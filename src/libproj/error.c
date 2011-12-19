/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   error.c - defines macros and functions for library-wide error handling
*   Created on December 14, 2011
*/
#include <config.h>
#include <error.h>

#define THIS_FILE "lperror"

void _lp_error(unsigned char lp_errno, lp_str err_msg, 
  lp_str file)
{ 
  if (file == NULL)
    file = _essential_data.title;

  if (lp_errno & 0x02)
    fprintf(stderr, "%s: %s (code %d)\n", file, err_msg, lp_errno);
  
  if (lp_errno & 0x01)
    exit(lp_errno);
}