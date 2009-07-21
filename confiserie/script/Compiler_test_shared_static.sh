#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

__opts() {
CONFIGURE_OPTS[__idx__]="--static=,ENABLE_STATIC_LIBS,enable static lib build,[yes|no],no"
CONFIGURE_OPTS[__idx__]="--dynamic=,ENABLE_DYNAMIC_LIBS,enable static lib build,[yes|no],yes"
}

mytest() {
        [ -z "${LIB_DIR}"  ] && echo "LIB_DIR isn't set, you must provide the path where the library sources and makefile is located"
        [ -z "${AR}"  ] && runtest ${confiserie}/tools/test_ar.sh
        [ -z "${LD}"  ] && runtest ${confiserie}/tools/test_ld.sh


        confiserie=${confiserie:=..}
        . ${confiserie}/confiserie.cache.functions.sh

        test -d .confiserietmp && rm -r .confiserietmp
        echo ${TEST_SEPARATOR}
        echo test_shared_static : testing library extention
        cp -R ${LIB_DIR} .confiserietmp              &&
        OLDPWD=${PWD}                                &&
        cd .confiserietmp                            &&
        {
                if [ "$ENABLE_STATIC_LIBS" == no ] && [ "$ENABLE_DYNAMIC_LIBS" == no ]; then
                        echo "disabling both static and dynamic libs, nonsense"
                        return 1
                fi

                if [ "$ENABLE_STATIC_LIBS" == no ]; then
                        echo "WARNING : --static=no, static libs will not be build"
                        echo "          unless shared libs aren't available"
                elif [ "$ENABLE_STATIC_LIBS" == yes ]; then
                        echo "----------------------------"
                        echo "testing if ar archives are supported"
                        export STATICLIBEXT=".a";
                        make clean
                        make || unset STATICLIBEXT;
                        STATIC_RESULT=${STATICLIBEXT};
                        unset STATICLIBEXT
                else 
                        echo "unknow value --static=$ENABLE_STATIC_LIBS"
                        return -1
                fi &&
                if [ "$ENABLE_DYNAMIC_LIBS" == no ]; then
                        echo "WARNING : --dynamic=no, dynamic libs will not be build"
                elif [ "$ENABLE_DYNAMIC_LIBS" == yes ]; then
                        echo "testing for shared lib format"
                        {
                                make clean
                                echo "----------------------------"
                                echo "testing if elf .so are supported"
                                export SHAREDLIBEXT=".so";
                                make
                        } ||
                        {
                                make clean
                                echo "----------------------------"
                                echo "testing if dll are supported"
                                export SHAREDLIBEXT=".dll";
                                make
                        } ||
                        {
                                make clean
                                unset SHAREDLIBEXT
                                echo "----------------------------"
                                echo "testing if ar archives are supported"
                                export STATICLIBEXT=".a";
                                make || unset STATICLIBEXT;
                        }
                else
                        echo "unknow value --dynamic=$ENABLE_DYNAMIC_LIBS"
                        return -1
                fi
        }

        cd ${OLDPWD}
        rm -r .confiserietmp
        STATICLIBEXT=${STATIC_RESULT}

        conf_cache STATICLIBEXT
        conf_cache SHAREDLIBEXT

        if [ -z "$STATICLIBEXT" ] && [ -z "$SHAREDLIBEXT" ]; then
                echo "can't determine extension.... " >&2
                return 1
        fi
}

mytest
