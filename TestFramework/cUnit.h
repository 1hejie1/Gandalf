/**
 * File:          $RCSfile: cUnit.h,v $
 * Module:        Test framework top-level program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.4 $
 * Last edited:   $Date: 2002/05/16 08:43:06 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

#include <gandalf/common/linked_list.h>
#include <gandalf/TestFramework/path_builder.h>

#ifndef CUNIT_H
#define CUNIT_H

// Note: the path structure from the executable to the test input/output directories
// will not be the same when running tests for SUB packages in test suite and 
// standalone configuration, and therefore these defines will be redefined in the SUB
// packages. 
// For normal packages residing in directories directly off the project root, 
// redefition should not be necessary.
// 
#ifdef _MSC_VER
   #define TEST_INPUT_PATH "./../gandalf/TestInput/"
   #define TEST_OUTPUT_PATH "./../gandalf/TestOutput/"
#else
   #define TEST_INPUT_PATH "./../TestInput/"
   #define TEST_OUTPUT_PATH "./../TestOutput/"
#endif

/* Use cUnit_assert in the unit tests */
#define cu_assert(expr) \
        if (!(expr)){ \
                printf ("%s\nLine %d in %s(): assert failed.\n\n",\
                __FILE__, \
                __LINE__, \
                #expr); return GAN_FALSE;}

#ifdef __cplusplus
extern "C" {
#endif

typedef Gan_Bool (*cUnit_setup_fp) ( void );

typedef Gan_Bool (*cUnit_test_fp) ( void );

typedef Gan_Bool (*cUnit_teardown_fp) ( void );

typedef struct cUnit_test_suite {
        int type;
        char* name;

        cUnit_setup_fp setup;
        cUnit_teardown_fp teardown;

        Gan_List *pTestList;
} cUnit_test_suite;

typedef struct cUnit_test {
        int type;
        char* name;

        cUnit_test_fp run;
} cUnit_test;

#ifdef __BORLANDC__
int run(int argc, char *argv[]);
#endif

typedef cUnit_test_suite* (*cUnit_build_test_suite_fp)(void);

void cUnit_add_test(cUnit_test_suite* ps, char* name, cUnit_test_fp test_func);

Gan_Bool cUnit_register_setup(cUnit_test_suite* ps, cUnit_setup_fp setup_func);

Gan_Bool cUnit_register_teardown(cUnit_test_suite* ps, cUnit_teardown_fp teardown_func);

cUnit_test_suite* cUnit_new_test_suite(char *name);

#ifdef __cplusplus
}
#endif

#endif
