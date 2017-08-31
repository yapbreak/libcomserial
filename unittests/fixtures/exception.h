#ifndef EXCEPTION_H_JZUMRNSW
#define EXCEPTION_H_JZUMRNSW

#include <CppUTest/TestHarness.h>

template<class C>
static inline void check_exception(const char *what)
{
    C *pe = NULL;
    pe = new C();
    STRCMP_EQUAL(what, pe->what());
    delete pe;
};


#endif /* end of include guard: EXCEPTION_H_JZUMRNSW */
