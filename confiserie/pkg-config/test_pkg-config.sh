#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
mytest() {
	WHICH=${WHICH:=which}
	confiserie=${confiserie:=..}
	. ${confiserie}/confiserie.cache.functions.sh

	printf "testing for pkg-config install path : "

	pkg_config=$(${WHICH} pkg-config)

	if [ -z ${pkg_config} ]; then
		printf pkg-config not found.
		return 1
	fi
	PKG_CONFIG_INSTALL_DIR=${pkg_config%/bin/pkg-config} &&
	PKG_CONFIG_INSTALL_DIR="${PKG_CONFIG_INSTALL_DIR}/lib/pkgconfig" &&
	conf_cache PKG_CONFIG_INSTALL_DIR
}

mytest

