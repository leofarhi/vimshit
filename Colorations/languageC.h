#ifndef COLORATION_LANGUAGE_C_H
#define COLORATION_LANGUAGE_C_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TabStruct.h"

void setTagColorC(TabStruct *tabStruct);
void colorizeC(TabStruct *tabStruct);

//all words in blue
//int, double, char, float, void, short, long, unsigned, signed, struct, union, enum, typedef, static, extern, auto, register, const, volatile, inline, restrict, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint
//all words in orange
//if, else, switch, case, default, for, while, do, break, continue, goto, return, sizeof, alignof, alignas, _Alignof, _Alignas, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size_t, _Wchar_t, _Wint_t, _Bool, _Complex, _Imaginary, _Noreturn, _Thread_local, _Atomic, _Alignas, _Alignof, _Generic, _Static_assert, _Pragma, _Nonnull, _Null_unspecified, _Nullable, _Null, _Ptr, _Ptrdiff_t, _Size
//all words in purple is #word
//incl
#define c_Word_blue_size 21
static char* c_Word_blue[c_Word_blue_size] = {
    "int",
    "double",
    "char",
    "float",
    "void",
    "short",
    "long",
    "unsigned",
    "signed",
    "struct",
    "union",
    "enum",
    "typedef",
    "static",
    "extern",
    "auto",
    "register",
    "const",
    "volatile",
    "inline",
    "restrict"
};

#define c_Word_purple_size 23
static char* c_Word_purple[c_Word_purple_size] = {
    "include",
    "define",
    "undef",
    "ifdef",
    "ifndef",
    "if",
    "elif",
    "else",
    "endif",
    "error",
    "pragma",
    "line",
    "defined",
    "switch",
    "case",
    "default",
    "break",
    "continue",
    "goto",
    "return",
    "sizeof",
    "alignof",
    "alignas",
};


#endif