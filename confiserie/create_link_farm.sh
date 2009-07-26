#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

mytest() {
	if [ "${ENABLE_LINK_FARM}" = "YES" ]; then
		if [ -n "${TOPSRC_DIR}" ] && [ -n "${OBJDIR}" ] && 
			[ "${TOPSRC_DIR}" != "${OBJDIR}" ];
		then
			printf ${TEST_SEPARATOR}
			printf "$0 creating link farm\n"
			if ! [ -d "${OBJDIR}" ] ; then
				if [ -a "${OBJDIR}" ] ; then
					printf "${OBJDIR} isn't a directory\n"
					exit 1
				fi
				mkdir -p ${OBJDIR}
			fi

			find ${TOPSRC_DIR} -type d -printf '%P\n' | 
			xargs -i mkdir -p ${OBJDIR}/{}

			find ${TOPSRC_DIR} -type f -printf '%P\n' | 
			xargs -i ln -s ${TOPSRC_DIR}/{} ${OBJDIR}/{}
			printf "$0 link farm created\n"
		fi
	else 
		if [ -n "${TOPSRC_DIR}" ] && [ -n "${OBJDIR}" ] && 
			[ "${TOPSRC_DIR}" != "${OBJDIR}" ];
		then
			printf "link farm creation desactivated while required... \n"
			printf "expecting package to rely on VPATH\n"
			printf "enable it with --enable-link-farm=YES option\n\n"
		fi
	fi
}


mytest

