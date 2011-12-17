/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   error.h - defines macros and functions for library-wide error handling
*   Created on December 14, 2011
*/

#ifndef LIBPROJ
# define LIBPROJ
#endif

#ifndef LPERROR_H

#define LPERROR_H

#include "base.h"

#define lp_error(e, m) _lp_error(e, m, THIS_FILE)

/*  Libproj error number scheme:
*   Six most significant bits represent unique code
*   7th bit is a flag for printing the supplied message
*   8th bit is a flag for exiting immediately
*/

void _lp_error(unsigned char lp_errno, lp_str err_msg, 
  lp_str file);

#endif /* LPERROR_H */