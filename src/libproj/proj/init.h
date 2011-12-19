/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   init.h - defines functions and variables used throughout
*   programs utilizing libproj.
*   Created on December 18, 2011
*/

#ifndef LIBPROJ
# define LIBPROJ
#endif

#ifndef LPINIT_H

#define LPINIT_H

#ifndef LPBASE
# include "base.h"
#endif

lp_str _prog_name;

struct _basic_data
  {
    lp_str title;
    lp_str version;
    lp_str extra;
    void *data;
  };

typedef struct _basic_data lp_data;

extern lp_data _essential_data;

extern void lp_set_prog_name(lp_str name);

extern void lp_register_data(lp_data re_data);

extern void lp_set_prog_vers(lp_str version);

#endif /* LPINIT_H */