#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

if test -z "${__UNIQ_TEST}"; then
    __UNIQ_TEST=sourced

    mytest() {
        #if WHICH as been defined, then use it, else use which
        WHICH=${WHICH:=which}
        confiserie=${confiserie:=..}
        . ${confiserie}/confiserie.cache.functions.sh


        #now the test
        printf "checking for uniq "
        if test -z "$UNIQ"; then
            if UNIQ=$(${WHICH} uniq 2>/dev/null); then
                conf_cache UNIQ
            else
                printf "not found...\n" >&2
                return 1
            fi
        fi
        return 0
    }

    mytest
fi
