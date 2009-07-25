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

	split_linker_flags()
	{
		while [ $# -gt 0 ]; do
			[ $1 = "-Wl" ] && continue;
			printf "$1 "
		done
	}

	OLD_IFS="${IFS}"
	LINKERFLAGS=$(IFS=', ' split_linker_flags ${LDFLAGS})
	conf_cache LDFLAGS
	conf_cache LINKERFLAGS

	LD=$(${WHICH} ld)
	conf_cache LD

}
mytest
