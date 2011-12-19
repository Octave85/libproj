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

#ifndef LPBASE
# include "base.h"
#endif

#ifndef LPINIT_H
# include "init.h"
#endif

#define lp_error(e, m, f) _lp_error(e, m, f)

/*  Libproj error number scheme:
*   Six most significant bits represent unique code
*   7th bit is a flag for printing the supplied message
*   8th bit is a flag for exiting immediately
*/

void _lp_error(unsigned char, lp_str, 
  lp_str);

#endif /* LPERROR_H */