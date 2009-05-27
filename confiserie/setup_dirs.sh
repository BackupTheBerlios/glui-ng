#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
confiserie=${confiserie:=.}
. ${confiserie}/confiserie.cache.functions.sh

export INSTALL_PREFIX=${INSTALL_PREFIX:=/usr}
export BIN_DIR=\${DESTDIR}${INSTALL_PREFIX}/${BINDIR:=bin}
export SBIN_DIR=\${DESTDIR}${INSTALL_PREFIX}/${SBINDIR:=sbin}
export LIB_DIR=\${DESTDIR}${INSTALL_PREFIX}/${LIBDIR:=lib}
export LIBEXEC_DIR=\${DESTDIR}${INSTALL_PREFIX}/${LIBEXEC_DIR:=libexec}
export SYS_CONF=\${DESTDIR}${SYSCONF:=/etc}
export SHARED_DATA_DIR=\${DESTDIR}${SHARED_DATA_DIR:=/usr/share}
export INCLUDE_DIR=\${DESTDIR}${INCLUDE_DIR:=/usr/include}

conf_cache INSTALL_PREFIX
conf_cache BIN_DIR
conf_cache SBIN_DIR
conf_cache LIB_DIR
conf_cache LIBEXEC_DIR
conf_cache SYS_CONF
conf_cache SHARED_DATA_DIR
conf_cache INCLUDE_DIR




