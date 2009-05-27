#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

mytest() {
        clean() {
                rm -rf *.o *.so *.a *.exe *.dll testlibconfiserie
        }

        create_objects() {
                ${CC} -c -o libconfiserie.o ${CPPFLAGS} ${CFLAGS} \
                      ${confiserie}/C/libconfiserie/libconfiserie.c 
                ${CC} -c -o libconfiserie2.o ${CPPFLAGS} ${CFLAGS} \
                      ${confiserie}/C/libconfiserie/libconfiserie2.c 
        }

        test_dll() {
                echo "----------------------------"
                echo "testing if dll are supported"
                ${CC} ${CC_LDFLAGS} -shared \
                -o libconfiserie.dll -Wl,--out-implib=libconfiserie.dll.a\
                -Wl,--export-all-symbols -Wl,--enable-auto-import \
                -Wl,--no-whole-archive  libconfiserie.o libconfiserie2.o&&
                ${CC} ${CC_LDFLAGS} -L. -lconfiserie -o testlibconfiserie \
                ${confiserie}/C/testlibconfiserie.c libconfiserie.dll.a&&
                SHAREDLIBEXT=".dll"
        }

        test_shared() {
                echo "----------------------------"
                echo "testing if elf .so are supported"
                ${LD} ${LDFLAGS} -shared -Bdynamic -soname libconfiserie.so \
                -o libconfiserie.so  libconfiserie.o libconfiserie2.o &&
                ${CC} ${CC_LDFLAGS} -L ./ -lconfiserie -o testlibconfiserie  \
                ${confiserie}/C/testlibconfiserie.c &&
                SHAREDLIBEXT=".so"
        }

        test_static() {
                echo "----------------------------"
                echo "testing if ar archives are supported"
                ${AR} -cr ${ARFLAGS} libconfiserie.a  libconfiserie.o libconfiserie2.o &&
                ${RANLIB} libconfiserie.a &&
                ${CC} ${CC_LDFLAGS} -o testlibconfiserie ${confiserie}/C/testlibconfiserie.c \
                ./libconfiserie.a &&
                STATICLIBEXT=".a"
        }


        CC=${CC:=gcc}
        LD=${LD:=ld}
        AR=${AR:=ar}
        RANLIB=${RANLIB:=ranlib}
        confiserie=${confiserie:=..}
        . ${confiserie}/confiserie.cache.functions.sh

        echo ${TEST_SEPARATOR} >&2
        echo test_shared_static : testing library extention >&2

        create_objects 1>/dev/null &&
        if [ -z "$ENABLE_STATIC" ]; then
                echo "WARNING : ENABLE_STATIC env not set, static libs will not be build"
                echo "          unless shared libs aren't available"
        else
                test_static 
        fi &&
        if [ -z "$DISABLE_DYNAMIC" ]; then
                echo "DISABLE_DYNAMIC env not set => testing for shared lib format"
                test_shared || test_dll || test_static
        fi &&

        clean

        conf_cache STATICLIBEXT
        conf_cache SHAREDLIBEXT
        conf_cache AR
        conf_cache RANLIB
        conf_cache ARFLAGS



        if [ -z "$STATICLIBEXT" ] && [ -z "$SHAREDLIBEXT" ]; then
                echo "can't determine extension.... " >&2
                return 1
        fi

}

mytest
