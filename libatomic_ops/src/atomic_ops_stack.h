/*
 * Copyright (c) 2005 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * The implementation of the routines described here is covered by the GPL.
 * This header file is covered by the above license.
 */

/* Almost lock-free LIFO linked lists (linked stacks).  */
#ifndef AO_STACK_H
#define AO_STACK_H

#include "atomic_ops.h"

#ifndef AO_HAVE_double_t
  /* Can happen if we are using CAS emulation, since we do not want to  */
  /* force that here, in case other atomic_ops clients do not want it.  */
# include "atomic_ops/sysdeps/standard_ao_double_t.h"
#endif

#ifdef __cplusplus
  extern "C" {
#endif

#ifdef AO_USE_ALMOST_LOCK_FREE
  /* Use the almost-non-blocking implementation regardless of the       */
  /* double-word CAS availability.                                      */
#elif !defined(AO_HAVE_compare_double_and_swap_double) \
      && !defined(AO_HAVE_compare_and_swap_double) \
      && defined(AO_HAVE_compare_and_swap)
# define AO_USE_ALMOST_LOCK_FREE
#else
  /* If we have no compare-and-swap operation defined, we assume        */
  /* that we will actually be using CAS emulation.  If we do that,      */
  /* it's cheaper to use the version-based implementation.              */
# define AO_STACK_IS_LOCK_FREE
#endif

/*
 * These are not guaranteed to be completely lock-free.
 * List insertion may spin under extremely unlikely conditions.
 * It cannot deadlock due to recursive reentry unless AO_list_remove
 * is called while at least AO_BL_SIZE activations of
 * AO_list_remove are currently active in the same thread, i.e.
 * we must have at least AO_BL_SIZE recursive signal handler
 * invocations.
 *
 * All operations take an AO_list_aux argument.  It is safe to
 * share a single AO_list_aux structure among all lists, but that
 * may increase contention.  Any given list must always be accessed
 * with the same AO_list_aux structure.
 *
 * We make some machine-dependent assumptions:
 *   - We have a compare-and-swap operation.
 *   - At least AO_N_BITS low order bits in pointers are
 *     zero and normally unused.
 *   - size_t and pointers have the same size.
 *
 * We do use a fully lock-free implementation if double-width
 * compare-and-swap operations are available.
 */

/* AO_stack_aux should be treated as opaque.  It is fully defined       */
/* here, so it can be allocated, and also to facilitate debugging.      */
/* Note: changing the value of AO_BL_SIZE leads to the ABI change.      */
#ifndef AO_BL_SIZE
# define AO_BL_SIZE 2
#endif

/* The number of low order pointer bits we can use for a small          */
/* version number.                                                      */
#if defined(__LP64__) || defined(_LP64) || defined(_WIN64)
# define AO_N_BITS 3
#else
# define AO_N_BITS 2
#endif

#define AO_BIT_MASK ((1 << AO_N_BITS) - 1)

#if AO_BL_SIZE > (1 << AO_N_BITS)
# error AO_BL_SIZE too big
#endif

#ifndef AO_STACK_ATTR_ALLIGNED
  /* Enforce proper alignment of AO_stack_t.AO_pa to avoid the          */
  /* structure value to cross the CPU cache line boundary.              */
  /* A workaround for almost-lock-free push/pop test failures           */
  /* on aarch64, at least.                                              */
# if AO_BL_SIZE == 1
    /* AO_vp is double-word aligned, so no extra align of AO_pa is needed.  */
#   define AO_STACK_ATTR_ALLIGNED /* empty */
# elif AO_GNUC_PREREQ(3, 1)
#   define AO_STACK_LOG_BL_SZP1 (AO_BL_SIZE > 7 ? 4 : AO_BL_SIZE > 3 ? 3 : 2)
#   define AO_STACK_ATTR_ALLIGNED \
        __attribute__((__aligned__(sizeof(AO_t) << AO_STACK_LOG_BL_SZP1)))
# elif defined(_MSC_VER) && _MSC_VER >= 1400 /* Visual Studio 2005+ */
    /* MS compiler accepts only a literal number in align, not expression.  */
    /* AO_STACK_ALLIGN_N is 1 << (AO_N_BITS + AO_STACK_LOG_BL_SZP1).        */
#   if AO_N_BITS > 2 && AO_BL_SIZE > 7
#     define AO_STACK_ALLIGN_N 128
#   elif (AO_N_BITS > 2 && AO_BL_SIZE > 3) || AO_BL_SIZE > 7
#     define AO_STACK_ALLIGN_N 64
#   elif AO_N_BITS > 2 || AO_BL_SIZE > 3
#     define AO_STACK_ALLIGN_N 32
#   else
#     define AO_STACK_ALLIGN_N 16
#   endif
#   define AO_STACK_ATTR_ALLIGNED __declspec(align(AO_STACK_ALLIGN_N))
# else
#   define AO_STACK_ATTR_ALLIGNED /* TODO: alignment is not enforced */
# endif
#endif /* !AO_STACK_ATTR_ALLIGNED */

typedef struct AO__stack_aux {
  volatile AO_t AO_stack_bl[AO_BL_SIZE];
} AO_stack_aux;

struct AO__stack_ptr_aux {
  volatile AO_t AO_ptr;
  AO_stack_aux AO_aux;
};

/* The AO stack type.  Should be treated as opaque.                     */
/* Note: AO_stack_t variables are not intended to be local ones,        */
/* otherwise it is the client responsibility to ensure they have        */
/* double-word alignment.                                               */
typedef union AO__stack {
  AO_STACK_ATTR_ALLIGNED struct AO__stack_ptr_aux AO_pa;
  volatile AO_double_t AO_vp;
} AO_stack_t;

/* The static initializer of the AO stack type. */
#define AO_STACK_INITIALIZER { /* .AO_pa= */ { 0, { {0} } } }

#ifdef AO_USE_ALMOST_LOCK_FREE
  /* The following two routines should not normally be used directly.   */
  /* We make them visible here for the rare cases in which it makes     */
  /* sense to share the AO_stack_aux between stacks.                    */

  AO_API void
  AO_stack_push_explicit_aux_release(volatile AO_t *list, AO_t *new_element,
                                     AO_stack_aux *);

  AO_API AO_t *
  AO_stack_pop_explicit_aux_acquire(volatile AO_t *list, AO_stack_aux *);
#endif /* AO_USE_ALMOST_LOCK_FREE */

#ifndef AO_REAL_PTR_AS_MACRO
  /* The stack implementation knows only about the location of  */
  /* link fields in nodes, and nothing about the rest of the    */
  /* stack elements.  Link fields hold an AO_t, which is not    */
  /* necessarily a real pointer.  This converts the AO_t to a   */
  /* real (AO_t *) which is either NULL, or points at the link  */
  /* field in the next node.                                    */
# define AO_REAL_NEXT_PTR(x) AO_stack_next_ptr(x)

  /* Convert an AO_stack_t to a pointer to the link field in    */
  /* the first element.                                         */
# define AO_REAL_HEAD_PTR(x) AO_stack_head_ptr(&(x))

#elif defined(AO_USE_ALMOST_LOCK_FREE)
# define AO_REAL_NEXT_PTR(x) (AO_t *)((x) & ~AO_BIT_MASK)
# define AO_REAL_HEAD_PTR(x) AO_REAL_NEXT_PTR((x).AO_pa.AO_ptr)
#else
# define AO_REAL_NEXT_PTR(x) (AO_t *)(x)
# define AO_REAL_HEAD_PTR(x) (AO_t *)((x).AO_vp.AO_val2 /* ptr */)
#endif /* AO_REAL_PTR_AS_MACRO && !AO_USE_ALMOST_LOCK_FREE */

AO_API void AO_stack_push_release(AO_stack_t *list, AO_t *new_element);
#define AO_HAVE_stack_push_release

#define AO_stack_push(l, e) AO_stack_push_release(l, e)
#define AO_HAVE_stack_push

AO_API AO_t *AO_stack_pop_acquire(AO_stack_t *list);
#define AO_HAVE_stack_pop_acquire

#define AO_stack_pop(l) AO_stack_pop_acquire(l)
#define AO_HAVE_stack_pop

AO_API void AO_stack_init(AO_stack_t *list);
AO_API int AO_stack_is_lock_free(void);

AO_API AO_t *AO_stack_head_ptr(const AO_stack_t *list);
AO_API AO_t *AO_stack_next_ptr(AO_t /* next */);

#ifdef __cplusplus
  } /* extern "C" */
#endif

#endif /* !AO_STACK_H */
