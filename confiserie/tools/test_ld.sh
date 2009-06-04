#/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2005 MALET Jean-luc aka cityhunter
#* This program is free software; you can redistribute it and/or modify
#* it under the terms of the artistic license as published at
#* http://cityhunter.is-a-geek.org/TESTAMENT
#************************************************************************/
WHICH=${WHICH:=which}
confiserie=${confiserie:=..}
. ${confiserie}/confiserie.cache.functions.sh

mytest() {
	if [ "${LDFLAGS:0:3}" == "-Wl" ]; then
		echo "......................................................................" >&2
		echo "WARNING use of -Wl (CC instruction) inside LDFLAGS... using workaround" >&2
		echo "......................................................................" >&2
		export CC_LDFLAGS=$LDFLAGS
		LDFLAGS=${LDFLAGS/-Wl/}
		LDFLAGS=${LDFLAGS/,/ }
	fi
	conf_cache LDFLAGS
	conf_cache CC_LDFLAGS

	LD=$(${WHICH} ld)
	conf_cache LD

}

mytest
