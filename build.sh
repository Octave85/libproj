#!/bin/bash
gcc -g -O2 -c lib/lpopts.c lib/error.c lib/init.c
if [ $? = 1 ]; then
  echo $0: build error
  exit 1;
fi

ar cru libproj.a lpopts.o error.o init.o;
ranlib libproj.a;
rm lpopts.o error.o init.o;
sudo install libproj.a /usr/lib/
if [ ! -d /usr/include/proj ]; then
  sudo mkdir /usr/include/proj
fi

sudo install lib/proj.h /usr/include
sudo install lib/proj/lpopts.h /usr/include/proj
sudo install lib/proj/error.h /usr/include/proj
sudo install lib/proj/base.h /usr/include/proj
sudo install lib/proj/init.h /usr/include/proj