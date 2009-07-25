#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

if test -z "${__CACHE_FUNC}"; then
    __CACHE_FUNC=sourced
    conf_cache() {
        eval export $1=\$$1
        export MODIFIED_ENV="$(printf "${MODIFIED_ENV}\n$1" |${SORT} |${UNIQ})"
        eval printf "$1=\$$1\\\\n"
    }

    mytest() {
        [ -z "${SORT}" ] && runtest ${confiserie}/tools/sort.sh                 &&
        [ -z "${UNIQ}" ] && runtest ${confiserie}/tools/uniq.sh
    }

    mytest
fi
