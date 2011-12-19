/*  libproj - Library of common programmatical functions
*   this file is part of libproj.
*   init.c - defines functions and variables used throughout
*   programs utilizing libproj.
*   Created on December 18, 2011
*/
#include <config.h>
#include <init.h>

#define THIS_FILE "lpinit"

lp_data _essential_data;

//_essential_data.title = "lp default name";
//_essential_data.version = "0.1";

void lp_set_prog_name(lp_str name)
{
  assert(name != NULL); 
  _essential_data.title = name;
}

void lp_set_prog_vers(lp_str version)
{
  assert(version != NULL);
  _essential_data.version = version;
}

void lp_register_data(lp_data re_data)
{
  assert(re_data.title != NULL);
  assert(re_data.version != NULL);

  _essential_data = re_data;
}