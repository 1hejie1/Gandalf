/**************************************************************************
*
* File:          $RCSfile: copy_file.c,v $
* Module:        Common package example program
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.1 $
* Last edited:   $Date: 2005/11/08 20:29:54 $
* Author:        $Author: pm $
* Copyright:     (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       
*
**************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <gandalf/common/file_io.h>

static void print_arguments(const char* progname)
{
   fprintf(stderr, "Usage: %s <source file> <dest file>\n", progname);
   exit(EXIT_FAILURE);
}

int main ( int argc, char *argv[] )
{
   if(argc != 3)
      print_arguments(argv[0]);

   if(!gan_file_copy(argv[1], argv[2]))
   {
      fprintf(stderr, "%s Failed\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
