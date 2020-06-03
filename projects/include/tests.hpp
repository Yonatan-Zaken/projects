/***************************
   Generic Tests File
      Header File
   Author : Greg Markovsky
     Date : 03/02/2020            
***************************/

#ifndef OL80_GREG_TESTS_H
#define OL80_GREG_TESTS_H

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

#define NEW_LINE printf("\n");
#define PRINT_COLOR_SET_TO_RED printf("\x1b[31m");
#define PRINT_COLOR_SET_TO_GREEN printf("\x1b[32m");
#define PRINT_COLOR_RESET printf("\x1b[0m");
#define DETAIL (1)
#define SILENT (0)
#define IGNORE (-1)
#define RUN_TEST(voc, name, test)\
					 if (IGNORE != voc) {TestStart(name, voc);\
			         test(voc);\
					 TestEnd(name, voc);}
#define RUN_TEST_PAR(voc, name, test, par)\
					 if (IGNORE != voc) {TestStart(name, voc);\
					 test(voc, par);\
					 TestEnd(name, voc);}
#define SET_LOG_PATHS(filename, level)\
	std::string envFilePath("ILRD_LOGGER_FILE_PATH=/home/student/projects/logger/");\
	envFilePath += filename;\
	std::string envLogLevel("ILRD_LOGGER_LEVEL=");\
	envLogLevel += level;\
	putenv((char *)envFilePath.c_str());\
	putenv((char *)envLogLevel.c_str());

void TestStart(const char *name, int voc);
void TestEnd(const char *name, int voc);
void TestBottomLine(const char *name);
void TestInt(int voc_status, const char *str, int exp, int rec);
void TestIntApp(int voc_status, const char *str, int exp, int rec, int margin);
void TestNotInt(int voc_status, const char *str, int exp, int rec);
void TestIntPos(int voc_status, const char *str, int rec);
void TestIntNeg(int voc_status, const char *str, int rec);
void TestDouble2(int voc_status, const char *str, double exp, double rec);
void TestSizeT(int voc_status, const char *str, size_t exp, size_t rec);
void TestSSizeT(int voc_status, const char *str, ssize_t exp, ssize_t rec);
void TestSizeTHex(int voc_status, const char *str, size_t exp, size_t rec);
void TestNotSizeTHex(int voc_status, const char *str, size_t exp, size_t rec);
void TestNotNull(int voc_status, const char *str, void *rec);
void TestPtr(int voc_status, const char *str, void *exp, void *rec);
void TestStr(int voc_status, const char *str, const char *exp, const char *rec);
void TestBytes(int voc_status, const char *str, 
				const char *exp, const char *rec, size_t bytes);
void TestIntArr(int voc_status, const char *str, 
				const int *exp, const int *rec, size_t arr_size);

#endif /* OL80_GREG_TESTS_H */


