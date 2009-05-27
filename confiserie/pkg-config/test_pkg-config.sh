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

	echo $TEST_SEPARATOR>&2
	echo "test_pkg-config.sh: testing for pkg-config install path">&2

	pkg_config=$(${WHICH} pkg-config) &&
	PKG_CONFIG_INSTALL_DIR=${pkg_config/\/bin\/pkg-config/} &&
	PKG_CONFIG_INSTALL_DIR="\${DESTDIR}${PKG_CONFIG_INSTALL_DIR}/lib/pkgconfig" &&
	conf_cache PKG_CONFIG_INSTALL_DIR
}

mytest

