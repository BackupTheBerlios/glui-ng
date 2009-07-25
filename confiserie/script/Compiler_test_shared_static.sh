#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

##CONFIGURE_OPTS --static= ENABLE_STATIC_LIBS "enable static lib build" "yes no" no
##CONFIGURE_OPTS --dynamic= ENABLE_DYNAMIC_LIBS "enable static lib build" "yes no" yes

mytest() {
        [ -z "${LIB_DIR}"  ] && printf "LIB_DIR isn't set, you must provide the path where the library sources and makefile is located\n"
        [ -z "${AR}"  ] && runtest ${confiserie}/tools/test_ar.sh
        [ -z "${LD}"  ] && runtest ${confiserie}/tools/test_ld.sh


        confiserie=${confiserie:=..}
        . ${confiserie}/confiserie.cache.functions.sh

        test -d .confiserietmp && rm -r .confiserietmp
        printf "${TEST_SEPARATOR}\n"
        printf "testing library extention\n"
        cp -R ${LIB_DIR} .confiserietmp              &&
        OLDPWD=${PWD}                                &&
        cd .confiserietmp                            &&
        {
                if [ "$ENABLE_STATIC_LIBS" = no ] && [ "$ENABLE_DYNAMIC_LIBS" = no ]; then
                        printf "disabling both static and dynamic libs, nonsense\n"
                        return 1
                fi

                if [ "$ENABLE_STATIC_LIBS" = no ]; then
                        printf "WARNING : --static=no, static libs will not be build"
                        printf "          unless shared libs aren't available\n"
                elif [ "$ENABLE_STATIC_LIBS" = yes ]; then
                        printf " ----------------------------\n"
                        printf "testing if ar archives are supported\n"
                        export STATICLIBEXT=".a";
                        make clean
                        make || unset STATICLIBEXT;
                        STATIC_RESULT=${STATICLIBEXT};
                        unset STATICLIBEXT
                else 
                        printf "unknow value --static=$ENABLE_STATIC_LIBS\n"
                        return -1
                fi &&
                if [ "$ENABLE_DYNAMIC_LIBS" = no ]; then
                        printf "WARNING : --dynamic=no, dynamic libs will not be build\n"
                elif [ "$ENABLE_DYNAMIC_LIBS" = yes ]; then
                        printf "testing for shared lib format\n"
                        {
                                make clean
                                printf " ----------------------------\n"
                                printf "testing if elf .so are supported\n"
                                export SHAREDLIBEXT=".so";
                                make
                        } ||
                        {
                                make clean
                                printf " ----------------------------\n"
                                printf "testing if dll are supported\n"
                                export SHAREDLIBEXT=".dll";
                                make
                        } ||
                        {
                                make clean
                                unset SHAREDLIBEXT
                                printf " ----------------------------\n"
                                printf "testing if ar archives are supported\n"
                                export STATICLIBEXT=".a";
                                make || unset STATICLIBEXT;
                        }
                else
                        printf "unknow value --dynamic=$ENABLE_DYNAMIC_LIBS\n"
                        return -1
                fi
        }

        cd ${OLDPWD}
        rm -r .confiserietmp
        STATICLIBEXT=${STATIC_RESULT}

        conf_cache STATICLIBEXT
        conf_cache SHAREDLIBEXT

        if [ -z "$STATICLIBEXT" ] && [ -z "$SHAREDLIBEXT" ]; then
                printf "can't determine extension.... \n" >&2
                return 1
        fi
}

mytest
