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
			echo -n "-Wl,$1 "
			shift
		done
	}

	clean_LDFLAGS() {
		while [ $# -gt 0 ]; do
            if test "${1:0:4}" = "-Wl,"; then
                echo -n "${1:4} "
            else
                echo -n "$1 "
            fi
			shift
		done
	}

  echo ${TEST_SEPARATOR} >&2
  if [ -z "${CXX}" ]; then
    {
			echo "CXX not set trying autodetection"
			CXX=$(${WHICH} g++) ||
			CXX=$(${WHICH} c++) ||
			{
				echo "this package require a C++ compiler and no CXX variable exported!"
				echo "g++ or c++ are not found in PATH"
				echo "please setup a decent environnement before trying to compile"
				return 1
			}
    } >&2
  fi
	conf_cache CXX
	
  if [ -z "$CXXFLAGS" ]; then 
    {
			CXXFLAGS="-O2"
			echo "CXXFLAGS not set, using default '-O2'"
    } >&2
  fi
	conf_cache CXXFLAGS
	conf_cache CPPFLAGS
    LDFLAGS=$(clean_LDFLAGS $LDFLAGS)
    conf_cache LDFLAGS
	CXX_LDFLAGS="${CXX_LDFLAGS} $(create_CXX_LDFLAGS $LDFLAGS)";
	conf_cache CXX_LDFLAGS

  {
    echo "checking for C++ compiler version" 
    echo "$($CXX --version </dev/null 2>/dev/null ||
    $CXX -v </dev/null  2>/dev/null ||
    $CXX -V </dev/null 2>/dev/null )" 
  }>&2 

  if ! ${CXX} -o mytest ${CPPFLAGS} ${CXXFLAGS} ${CXX_LDFLAGS} ${confiserie}/CXX/simple.cpp 1>/dev/null; 
  then
    {
      echo "error in compiling CXX/simple.cpp" 
      echo "the command issued was "
      echo "${CXX} -o test ${CPPFLAGS} ${CFLAGS} ${CXX_LDFLAGS} ${confiserie}/CXX/simple.cpp" 
    }>&2
    rm -f mytest
		
    return 1 
  fi

  # Check the compiler produces executables we can run.  If not, either
  # the compiler is broken, or we cross compile.
  echo -n "checking whether the CXX compiler works : " >&2
  if test "$cross_compiling" != yes; then
    if ! ./mytest; then
      {
        echo "no" 
        echo "$0: error: cannot run CXX compiled programs. " 
        echo "If you meant to cross compile, use --crosscompile". 
      } >&2
      rm -f mytest
      return 1;
    fi
  fi
  echo "yes" >&2
  rm -f mytest

  return 0
}

mytest
