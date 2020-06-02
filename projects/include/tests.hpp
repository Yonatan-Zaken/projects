#include <stdio.h> /* size_t */

#ifndef OL80_GREG_TESTS_H
#define OL80_GREG_TESTS_H

#define NEW_LINE printf("\n");

#include <stdint.h> /* uint64_t */

void TestInt(const char *func, int exp, int rec);
void TestSizeT(const char *func, size_t exp, size_t rec);

#endif /* OL80_GREG_TESTS_H */
