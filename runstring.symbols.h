/*****
 * This file is automatically generated by findsym.pl
 * Changes will be overwritten.
 *****/

// If the ADDSYMBOL macro is not already defined, define it with the default
// purpose of referring to an external pre-translated symbol, such that
// SYM(name) also refers to that symbol.
#ifndef ADDSYMBOL
    #define ADDSYMBOL(name) extern sym::symbol PRETRANSLATED_SYMBOL_##name
    #define SYM(name) PRETRANSLATED_SYMBOL_##name
#endif

ADDSYMBOL(ascii);
ADDSYMBOL(digits);
ADDSYMBOL(downcase);
ADDSYMBOL(erase);
ADDSYMBOL(find);
ADDSYMBOL(format);
ADDSYMBOL(hex);
ADDSYMBOL(insert);
ADDSYMBOL(length);
ADDSYMBOL(locale);
ADDSYMBOL(n);
ADDSYMBOL(pos);
ADDSYMBOL(replace);
ADDSYMBOL(reverse);
ADDSYMBOL(rfind);
ADDSYMBOL(s);
ADDSYMBOL(seconds);
ADDSYMBOL(string);
ADDSYMBOL(substr);
ADDSYMBOL(t);
ADDSYMBOL(time);
ADDSYMBOL(translate);
ADDSYMBOL(upcase);
ADDSYMBOL(x);
