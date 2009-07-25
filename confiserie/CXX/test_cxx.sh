#/bin/sh 
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
WHICH=${WHICH:=which}
confiserie=${confiserie:=..}
. ${confiserie}/confiserie.cache.functions.sh

mytest() {

	create_CXX_LDFLAGS() {
		while [ $# -gt 0 ]; do
			printf "-Wl,$1 "
			shift
		done
	}

	clean_LDFLAGS() {
		while [ $# -gt 0 ]; do
            if test "${1:0:4}" = "-Wl,"; then
                printf "${1:4} "
            else
                printf "$1 "
            fi
			shift
		done
	}

  if [ -z "${CXX}" ]; then
    {
			printf "CXX not set trying autodetection \n"
			CXX=$(${WHICH} g++) ||
			CXX=$(${WHICH} c++) ||
			{
				printf "this package require a C++ compiler and no CXX variable exported!\n"
				printf "g++ or c++ are not found in PATH\n"
				printf "please setup a decent environnement before trying to compile\n"
				return 1
			}
    } >&2
  fi
	conf_cache CXX
	
  if [ -z "$CXXFLAGS" ]; then 
    {
			CXXFLAGS="-O2"
			printf "CXXFLAGS not set, using default '-O2'\n"
    } >&2
  fi
	conf_cache CXXFLAGS
	conf_cache CPPFLAGS
    LDFLAGS=$(clean_LDFLAGS $LDFLAGS)
    conf_cache LDFLAGS
	CXX_LDFLAGS="${CXX_LDFLAGS} $(create_CXX_LDFLAGS $LDFLAGS)";
	conf_cache CXX_LDFLAGS

  {
    printf "checking for C++ compiler version\n" 
    printf "$($CXX --version </dev/null 2>/dev/null ||
    $CXX -v </dev/null  2>/dev/null ||
    $CXX -V </dev/null 2>/dev/null )\n" 
  }>&2 

  if ! ${CXX} -o mytest ${CPPFLAGS} ${CXXFLAGS} ${CXX_LDFLAGS} ${confiserie}/CXX/simple.cpp 1>/dev/null; 
  then
    {
      printf "error in compiling CXX/simple.cpp\n" 
      printf "the command issued was \n"
      printf "${CXX} -o test ${CPPFLAGS} ${CFLAGS} ${CXX_LDFLAGS} ${confiserie}/CXX/simple.cpp\n" 
    }>&2
    rm -f mytest
		
    return 1 
  fi

  # Check the compiler produces executables we can run.  If not, either
  # the compiler is broken, or we cross compile.
  printf "checking whether the CXX compiler works : " >&2
  if test "$cross_compiling" != yes; then
    if ! ./mytest; then
      {
        printf "no\n" 
        printf "$0: error: cannot run CXX compiled programs. \n" 
        printf "If you meant to cross compile, use --crosscompile\n". 
      } >&2
      rm -f mytest
      return 1;
    fi
  fi
  printf "yes\n" >&2
  rm -f mytest

  return 0
}

mytest
