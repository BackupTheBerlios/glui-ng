#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/
which() {
  saveifs=$IFS
  IFS=:
	NOTFOUND=1
  for dir in $PATH
  do
    if  [ -f $dir/$1 ] && [ -x $dir/$1 ]; then 
      printf $dir/$1;
      $ALL || return 0
			NOTFOUND=0
    fi
  done
	
  return $NOTFOUND
}

process_args() {
	while [ "$#" -gt "0" ]; do
		case $1 in 
			-a) ALL=true;;
			*) which $1;;
		esac
		shift
	done
}

ALL=false
process_args "$@"
