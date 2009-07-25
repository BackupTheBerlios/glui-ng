#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

#note the fact that we can include functions definition into function....
#     the functions are then known only in the function.....
#note the name of the included function must be mytest, this is for 
#     preventing namespace polution in case of sourcing the script
#     this has several adavantages :
#        -> it consume less memory because when subsequent scripts are sourced
#           the provious function definition will be discarded
#        -> it prevent namespace polution : you won't have a previous script that
#           defined the same function name, conflict with yours....
#note the two line 'printf AWK=$AWK' and 'export AWK=$AWK' this allow sourcing the 
#     script and have the result available to later scripts, and keep the possibilty
#     to simply write the result to a file (makefile for exemple)
#note the WHICH=${WHICH:=which} that allow to have the test self runnable provided that
#     which is available
#note that the test only occurs if AWK variable isn't present (test -z "$AWK" line)
if test -z "${__TEST_AWK}"; then
    __TEST_AWK=sourced
    mytest() {
        WHICH=${WHICH:=which}
        confiserie=${confiserie:=..}
        . ${confiserie}/confiserie.cache.functions.sh

        if test -z "$AWK"; then
            for prog in gawk mawk nawk awk
            do
                printf "\ntest_awk.sh : checking for $prog : " >&2
                if AWK=$(${WHICH} $prog 2>/dev/null); then
                    conf_cache AWK
                    return 0
                else
                    printf "not found..." >&2
                fi
            done
            printf "\nno AWK found\n"
            return 1
        fi
    }

    mytest
fi


