# ---- asy tests ------

set(ASY_ASYLANG_TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(ASY_ASYLANG_TEST_SCRATCH_DIR ${ASY_ASYLANG_TEST_ROOT}/out/)

function(add_individual_asy_tests)
    set(fn_opts)
    set(fn_oneval_args DIR FILE ADDR_ASY_ARGS)
    set(fn_multival_args)
    cmake_parse_arguments(
            ASY_TEST "${fn_opts}" "${fn_oneval_args}" "${fn_multival_args}" ${ARGN}
    )

    set(TEST_PATH ${ASY_ASYLANG_TEST_ROOT}/${ASY_TEST_DIR}/${ASY_TEST_FILE}.asy)
    add_test(
            NAME "asy.${ASY_TEST_DIR}.${ASY_TEST_FILE}"
            COMMAND asy
                -dir ${ASY_BUILD_BASE_DIR} ${TEST_PATH}
                -noV
                -o out
                -globalwrite
                ${ASY_TEST_ADDR_ASY_ARGS}
            WORKING_DIRECTORY ${ASY_ASYLANG_TEST_ROOT}
    )
endfunction()

macro(add_asy_tests)
    set(macro_opts)
    set(macro_oneval_args TEST_DIR ADDR_ASY_ARGS)
    set(macro_multival_args TESTS TEST_ARTIFACTS)
    cmake_parse_arguments(
            ASY_TESTING "${macro_opts}" "${macro_oneval_args}" "${macro_multival_args}" ${ARGN}
    )
    foreach(testfile ${ASY_TESTING_TESTS})
        add_individual_asy_tests(
                DIR ${ASY_TESTING_TEST_DIR}
                FILE ${testfile}
                ADDR_ASY_ARGS ${ASY_TESTING_ADDR_ASY_ARGS}
        )
    endforeach()

    foreach(artifact ${ASY_TESTING_TEST_ARTIFACTS})
        set_property(
                TARGET asy
                APPEND
                PROPERTY ADDITIONAL_CLEAN_FILES ${ASY_ASYLANG_TEST_SCRATCH_DIR}/${artifact}
        )
    endforeach()
endmacro()

# ------ tests ----------

add_asy_tests(
        TEST_DIR arith
        TESTS integer pair random real roots transform triple
)
add_asy_tests(
        TEST_DIR array
        TESTS array delete determinant fields slice solve sort transpose
)
add_asy_tests(
        TEST_DIR frames
        TESTS loop stat stat2
)

if (ENABLE_GC)
    add_asy_tests(
            TEST_DIR gc
            TESTS array funcall guide label path shipout string struct transform
            TEST_ARTIFACTS .eps
    )
endif()

if (ENABLE_GSL)
    add_asy_tests(
            TEST_DIR gsl
            TESTS random
    )
endif()

add_asy_tests(TEST_DIR imp TESTS unravel)
add_asy_tests(TEST_DIR io TESTS csv)
add_asy_tests(TEST_DIR output TESTS circle line TEST_ARTIFACTS circle.eps line.eps)
add_asy_tests(TEST_DIR pic TESTS trans)
add_asy_tests(
        TEST_DIR string
        TESTS erase find insert length rfind substr
)
add_asy_tests(
        TEST_DIR types
        TESTS cast constructor ecast guide init keyword order resolve shadow spec var
)

add_asy_tests(
        TEST_DIR template
        TESTS initTest functionTest mapArrayTest multiImport singletype sortedsetTest splaytreeTest structTest
)

add_asy_tests(
        TEST_DIR gs
        TESTS ghostscript
)
