#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
mytest() {
	PKG_CONFIG=${PKG_CONFIG:=pkg-config}

	printf "testing for pkg-config --print-errors %s\n" "$*"

        ${PKG_CONFIG} --print-errors  "$@"
        return $?
}

mytest "$@"

