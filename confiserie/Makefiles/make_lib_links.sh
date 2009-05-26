#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
# takes a filename of the form libfoo-x.y.z.ext and produce symlinks to 
# libfoo.so libfoo-x.so libfoo-x.y.so ....

create_links() {
	IFS=${oldifs}
	local intermediate
	local previous
	
	while [ "$#" -gt "0" ]; do
		if [ -z "${intermediate}" ]; then
			intermediate="-${1}"
		else
			intermediate=${intermediate}.${1}
		fi
		rm -f ${dirname}/${basename}${previous}.${extension}
		ln -s ${basename}${intermediate}.${extension} ${dirname}/${basename}${previous}.${extension} 	
		previous=${intermediate}
		shift
	done
}
oldifs=$IFS

while [ "$#" -gt "0" ]; do
	basename=${1/*\//}
	dirname=${1/$basename/}
	extension=${1/*./}
	basename=${basename/.${extension}/}
	version=${basename/*-/}
	test "${version}" == "${basename}"  && exit 0
	basename=${basename/-$version/}

	IFS=$'.'

	create_links $version
	shift
done

