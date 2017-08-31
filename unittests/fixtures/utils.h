#ifndef UTILS_H_CH4025PS
#define UTILS_H_CH4025PS

#include <CppUTest/TestHarness.h>
#include <vector>

#define DIM_OF(array) (sizeof(array) / sizeof((array)[0]))

#if HAVE_SOCAT == 1
#   define SOCAT_TEST TEST
#else
#   define SOCAT_TEST IGNORE_TEST
#endif

#define ARRAY(...) { __VA_ARGS__ }
#define check_frame(expect, type, ...) do { \
    std::vector<uint8_t> expected(expect); \
    type *f = new type(__VA_ARGS__); \
    UNSIGNED_LONGS_EQUAL(expected.size() + 2, f->get_frame().size()); \
    MEMCMP_EQUAL(expected.data(), f->get_frame().data(), expected.size()); \
    delete f; \
} while (0)

#endif /* end of include guard: UTILS_H_CH4025PS */
