#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

mytest() {
	echo >&2
	if [ "${ENABLE_LINK_FARM}" == "YES" ]; then
		if [ -n "${TOPSRC_DIR}" ] && [ -n "${OBJDIR}" ] && 
			[ "${TOPSRC_DIR}" != "${OBJDIR}" ];
		then
			echo ${TEST_SEPARATOR} >&2
			echo "$0 creating link farm" >&2
			if ! [ -d "${OBJDIR}" ] ; then
				if [ -a "${OBJDIR}" ] ; then
					echo "${OBJDIR} isn't a directory" >&2
					exit 1
				fi
				mkdir -p ${OBJDIR}
			fi

			find ${TOPSRC_DIR} -type d -printf '%P\n' | 
			xargs -i mkdir -p ${OBJDIR}/{}

			find ${TOPSRC_DIR} -type f -printf '%P\n' | 
			xargs -i ln -s ${TOPSRC_DIR}/{} ${OBJDIR}/{}
			echo "$0 link farm created" >&2
		fi
	else 
		if [ -n "${TOPSRC_DIR}" ] && [ -n "${OBJDIR}" ] && 
			[ "${TOPSRC_DIR}" != "${OBJDIR}" ];
		then
			echo "link farm creation desactivated while required... " >&2
			echo "expecting package to rely on VPATH" >&2
			echo "enable it with --enable-link-farm=YES option" >&2
			echo  >&2
		fi
	fi
}


mytest

