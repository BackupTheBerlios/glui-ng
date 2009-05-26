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
        export MODIFIED_ENV="$(echo ${MODIFIED_ENV} $1 |sort |uniq)"
        eval echo "$1=\$$1" >&2
    }

    mytest() {
        . ${confiserie}/tools/sort.sh &&
        . ${confiserie}/tools/uniq.sh
    }

    mytest
fi
