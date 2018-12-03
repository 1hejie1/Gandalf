/**
 * File:          $RCSfile: cUnit.c,v $
 * Module:        Test framework top-level program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.13 $
 * Last edited:   $Date: 2004/03/25 09:22:34 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* Adds test suites and runs test suites selected by the user */

#include <string.h>
#include <stdio.h>

#include <gandalf/TestFramework/cUnit.h>
#include <gandalf/common/linked_list.h>
#include <gandalf/common/allocate.h>
#include <gandalf/common/list_test.h>
#include <gandalf/common/common_test.h>
#include <gandalf/vision/vision_test.h>
#include <gandalf/vision/camera_test.h>
#include <gandalf/vision/hough_transform_test.h>
#include <gandalf/vision/convolve2D_test.h>
#include <gandalf/image/image_test.h>
#include <gandalf/image/bitmap_test.h>
#include <gandalf/linalg/linalg_test.h>
#include <gandalf/linalg/matrixf_eigen_test.h>

/* Reads the user selection from the keyboard */
unsigned int menu()
{
   char buffer[4];
   int ch;
   unsigned int uiSelect;
   
   /* Read each character and put it into the array */
   for (uiSelect = 0;
        (uiSelect < 3) && ((ch = getchar()) != EOF) && (ch != '\n');
        uiSelect++)
      buffer[uiSelect] = (char)ch;
   
   /* Terminate string with null character */
   buffer[uiSelect] = '\0';
   
   /* Reusing uiSelect, uiSelect will now be the test number to run */
   uiSelect = atoi(buffer);
   return uiSelect;
}

/* Prints out an error message when the user enters invalid command line arguments */
void print_banner()
{
   printf("Usage: cUnit [-wait] [[-all][-menu]]\n\n");
   printf("Press [RETURN] to end the program.");
   getchar();
   exit(EXIT_FAILURE);
}

/* Creates a new list for the test suites */
cUnit_test_suite* cUnit_new_test_suite(char *name)
{
   cUnit_test_suite *new_suite = (cUnit_test_suite *)
                                 malloc(sizeof(cUnit_test_suite));
   new_suite->pTestList = gan_list_new();
   return (new_suite);
}

/* Adds new tests to a test suite */
void cUnit_add_test(cUnit_test_suite* ps, char* name, cUnit_test_fp test_func)
{
   cUnit_test *pTest = (cUnit_test *) malloc(sizeof(cUnit_test));
   pTest->name = name;
   pTest->run = test_func;
   gan_list_insert_last(ps->pTestList, pTest);
}

/* frees a test suite */
static void cUnit_free_test_suite ( cUnit_test_suite* ps )
{
   gan_list_free ( ps->pTestList, free );
   free(ps);
}

Gan_Bool cUnit_register_setup(cUnit_test_suite* ps, cUnit_setup_fp setup_func)
{
   ps->setup = setup_func;
   return GAN_TRUE;
}

Gan_Bool cUnit_register_teardown(cUnit_test_suite* ps, cUnit_teardown_fp teardown_func)
{
   ps->teardown = teardown_func;
   return GAN_TRUE;
}

/* Adds new test suites */
cUnit_test_suite* cUnit_add_test_suite(char* pName, cUnit_build_test_suite_fp build_func)
{
   cUnit_test_suite* pSuite = build_func();
   pSuite->name = pName;
   return pSuite;
}

/* Runs all test suites in the auto test list */
static void run_all_suites(Gan_List *pSuiteList)
{
   cUnit_test *pTest;
   cUnit_test_suite *pSuite;
   unsigned int uiSuiteNum, uiTestNum, uiErrCount = 0;

   gan_list_goto_head(pSuiteList);

   /* Loop through the list and extract and run each test suite */
   for (uiSuiteNum = 0;uiSuiteNum < (unsigned int)pSuiteList->node_count;uiSuiteNum++)
   {
      pSuite = gan_list_get_next(pSuiteList, cUnit_test_suite);
      gan_list_goto_head(pSuite->pTestList);

      for (uiTestNum = 0;uiTestNum < (unsigned int)pSuite->pTestList->node_count;uiTestNum++)
      {
         pTest = gan_list_get_next(pSuite->pTestList, cUnit_test);
         pSuite->setup();

         if (pTest->run() == GAN_FALSE)
            uiErrCount++;
         
         pSuite->teardown();
      }

      if (uiErrCount == 0)
         printf("No errors encountered in %s\n", pSuite->name);
      else
         printf("%d error(s) encountered in %s\n", uiErrCount, pSuite->name);

      uiErrCount = 0;
   }
}   

/* Runs one suite selected by the user */
void run_one_suite(char* pchName, Gan_List *pSuiteList)
{
   cUnit_test *pTest;
   cUnit_test_suite *pSuite;
   unsigned int uiSuiteNum, uiTestNum, uiErrCount = 0;

   gan_list_goto_head(pSuiteList);

   /* Loop through the list of test suites to find a match */
   for (uiSuiteNum = 0;uiSuiteNum < (unsigned int)pSuiteList->node_count;uiSuiteNum++)
   {
      pSuite = gan_list_get_next(pSuiteList, cUnit_test_suite);

      /* If a match is found, run the test */
      if (pSuite->name == pchName)
      {
         gan_list_goto_head(pSuite->pTestList);
         
         for (uiTestNum = 0;uiTestNum < (unsigned int)pSuite->pTestList->node_count;uiTestNum++)
         {
            pTest = gan_list_get_next(pSuite->pTestList, cUnit_test);
            pSuite->setup();

            if (pTest->run() == GAN_FALSE)
               uiErrCount++;

            pSuite->teardown();
         }
         
         if (uiErrCount == 0)
            printf("No errors encountered in %s\n", pSuite->name);
         else
            printf("%d error(s) encountered in %s\n", uiErrCount, pSuite->name);
         
         return;
      }
   }
}

#ifdef __BORLANDC__  /*C++Builder*/
int run(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
#define maxAutoTests 11
#define maxVisualTests 0

   char* auto_tests[maxAutoTests];
   char* visual_tests[maxAutoTests + maxVisualTests];

   cUnit_test_suite* pSuite;
   Gan_Bool bWait;
   Gan_List *glstAutoSuiteList = gan_list_new();
   Gan_List *glstVisualSuiteList = gan_list_new();

   int iIndex;
   unsigned int uiTestNum, uiSelection;

   /* Array of auto test suites */
   iIndex=0;
   auto_tests[iIndex++] = "list_test";
   auto_tests[iIndex++] = "common_test";
   auto_tests[iIndex++] = "linalg_test";
   auto_tests[iIndex++] = "matrixf_eigen_test";
   auto_tests[iIndex++] = "image_test";
   auto_tests[iIndex++] = "bitmap_test";
   auto_tests[iIndex++] = "vision_test";
   auto_tests[iIndex++] = "camera_test";
   auto_tests[iIndex++] = "hough_transform_test";
   auto_tests[iIndex++] = "convolve2D_test";
   auto_tests[iIndex++] = "Run All Tests";
   if ( iIndex != maxAutoTests )
   {
      /* If the menu selection is invalid, print an error message */
      printf("Incorrect number of tests. Press [RETURN] to end the program.");
      getchar();
      exit(1);
   }

   /* Array of visual test suites */
   iIndex=0;
#if 0
   visual_tests[maxAutoTests + iIndex++] = "display_test";
#endif
   if ( iIndex != maxVisualTests )
   {
      /* If the menu selection is invalid, print an error message */
      printf("Incorrect number of tests. Press [RETURN] to end the program.");
      getchar();
      exit(1);
   }
   
   /* Add each test suite in the array to the list */
   /* AUTO TESTS */
   iIndex=0;
   pSuite = cUnit_add_test_suite(auto_tests[iIndex++], list_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 common_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 linalg_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 matrixf_eigen_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 image_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 bitmap_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 vision_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 camera_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 hough_transform_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   pSuite = cUnit_add_test_suite(auto_tests[iIndex++],
                                 convolve2D_test_build_suite);
   gan_list_insert_last(glstAutoSuiteList, pSuite);

   if ( iIndex != maxAutoTests-1 )
   {
      /* If the menu selection is invalid, print an error message */
      printf("Incorrect number of tests. Press [RETURN] to end the program.");
      getchar();
      exit(1);
   }

   /* VISUAL TESTS */
   iIndex=0;
#if 0
   pSuite = cUnit_add_test_suite(visual_tests[maxAutoTests + iIndex++],
                                 display_test_build_suite);
   gan_list_insert_last(glstVisualSuiteList, pSuite);
#endif
   if ( iIndex != maxVisualTests )
   {
      /* If the menu selection is invalid, print an error message */
      printf("Incorrect number of tests. Press [RETURN] to end the program.");
      getchar();
      exit(1);
   }

   /* If there are no command line arguments, print an error message */
   if(argc == 1)
      print_banner();

   /* If the command line argument is "-wait" only, print an error message */
   if(!strcmp(argv[1], "-wait"))
   {
      if(argc != 3)
         print_banner();
      
      bWait = GAN_TRUE;
      iIndex = 2;
   }
   else
   {
      bWait = GAN_FALSE;
      iIndex = 1;
   }

   /* If the command line argument is "-all", run all auto test suites */
   if(!strcmp(argv[iIndex], "-all"))
      run_all_suites(glstAutoSuiteList);

   /* If the command line argument is "-menu", print the test menu */
   if(!strcmp(argv[iIndex], "-menu"))
   {
      while (1)
      {
         printf("******* TEST MENU *******\n\n");
         printf("Automatic Tests:\n");
         printf("----------------\n\n");

         for(uiTestNum = 0; uiTestNum < maxAutoTests; uiTestNum++)
            printf("%3d : %s\n\n", uiTestNum+1, auto_tests[uiTestNum]);

         printf("\nVisual Tests:\n");
         printf("-------------\n\n");

         for(uiTestNum = maxAutoTests; uiTestNum < maxAutoTests+maxVisualTests; uiTestNum++)
            printf("%3d : %s\n\n", uiTestNum+1, visual_tests[uiTestNum]);

         printf("\n---------------\n\n");
         printf("Your selection (0 to exit) : ");
         uiSelection = menu();

         if (uiSelection==0)
         {
            gan_list_free ( glstAutoSuiteList,
                            (Gan_FreeFunc)cUnit_free_test_suite );
            gan_list_free ( glstVisualSuiteList,
                            (Gan_FreeFunc)cUnit_free_test_suite );
            gan_heap_report(NULL);
            exit(EXIT_SUCCESS);    
         }
         else  if (uiSelection > maxAutoTests+maxVisualTests)
         {
            /* If the menu selection is invalid, print an error message */
            printf("The selection is invalid. Press [RETURN] to end the program.");
            getchar();
            exit(1);
         }

         uiSelection-=1; // Modifiy selection to array index

         /* If the menu selection is the last option in the auto test list,
          * run all suites. Otherwise, run the selected test suite
          */
         if (uiSelection == (maxAutoTests - 1))
            run_all_suites(glstAutoSuiteList);
         else
         {
            if(uiSelection < maxAutoTests - 1)
               run_one_suite(auto_tests[uiSelection], glstAutoSuiteList);
            else
               run_one_suite(visual_tests[uiSelection], glstVisualSuiteList);
         }
      }
   }

   if (bWait == GAN_TRUE)
      getchar();

   gan_list_free ( glstAutoSuiteList,   (Gan_FreeFunc)cUnit_free_test_suite );
   gan_list_free ( glstVisualSuiteList, (Gan_FreeFunc)cUnit_free_test_suite );
   gan_heap_report(NULL);
   exit(EXIT_SUCCESS);
}
