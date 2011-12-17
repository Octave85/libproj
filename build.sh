#!/bin/bash
gcc -g -O2 -c lib/lpopts.c lib/error.c;
ar cru libproj.a lpopts.o error.o;
rm lpopts.o error.o;
gcc -g -O2 -o $2 $1 libproj.a;
