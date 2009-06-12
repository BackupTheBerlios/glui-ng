#!/bin/sh
#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

#this script is dedicated to system initialisation
#you should put here only what is needed to make the scripts run
#others test must go elsewhere
confiserie=${confiserie:=.}

unset MODIFIED_ENV

PACKAGE_OPTS_COUNT=${#CONFIGURE_OPTS[@]}
CONFIGURE_OPTS[$((PACKAGE_OPTS_COUNT+1))]="--prefix=,PREFIX,configure package to be located in prefix [path],/usr/local"
CONFIGURE_OPTS[$((PACKAGE_OPTS_COUNT+2))]="--crosscompiling=,CROSSCOMPILING,the package is crosscompiled [YES|NO],NO"
CONFIGURE_OPTS[$((PACKAGE_OPTS_COUNT+3))]="--enable-link-farm=,ENABLE_LINK_FARM,enable link farm creation [YES|NO],NO"
PACKAGE_OPTS_COUNT=${#CONFIGURE_OPTS[@]}


#interactive_conf() {
#	
#	ask_user() {
#		var=$2
#		default=$4
#	}
#
#	
#	local i
#	OLDIFS=${IFS}
#	IFS=$','
#	while [ "$i" -lt "$PACKAGE_OPTS_COUNT" ]; do
#		
#}

parse_opts() {

	assign_defaults() {
		var=$2
		default=$4
		if [ -n "$default" ]; then
			eval $var=$default
                        conf_cache $var
		fi
	}

	read_vars() {
		long=$1
		var=$2
	}
	
	local cur_pos
	OLDIFS=${IFS}

	IFS=$','
	cur_pos=1
	while [ ${cur_pos} -le ${PACKAGE_OPTS_COUNT} ]; do
		assign_defaults ${CONFIGURE_OPTS[$cur_pos]}
		cur_pos=$(($cur_pos + 1))
	done

	while [  "$#" -gt 0 ]; do
		cur_pos=1
		while [ ${cur_pos} -le ${PACKAGE_OPTS_COUNT} ]; do
#			IFS=$','
			read_vars ${CONFIGURE_OPTS[$cur_pos]} 
			case $1 in
				-h|--help) display_help >&2; exit 0;;
				-V|--version*) echo "$0 : 0.0.2"; exit 0;;
				--interactive) interactive_conf;;
				$long*) eval export $var=${1##$long}; conf_cache $var;;
			esac
			cur_pos=$(($cur_pos + 1))
		done
		shift

	done
	IFS=${OLDIFS}
}

	

display_help() {


	format_option() {
		echo -e "\t$1\n\t\tresult in $2, $3, default:$4"
	}

	cat <<-EOF
	Configuration :
	  -h, --help              display this help and exit
	  -V, --version           display version information and exit
		--interactive           do interactive configuration, all options
		                        are prompted for answer
	

	Some influential environment variables:
	  //see man gcc or whatever compiler you're using
	  CC          C compiler command, if possible, set an absolute path
	            and avoid options
	  CFLAGS      C compiler flags, use this to define optimisations and 
	            everything related to compilation (and not linkage nor
	            preprossing)
	  CPPFLAGS    C/C++ preprocessor flags, e.g. -I<include dir> if you have
	            headers in a nonstandard directory <include dir>, and 
	            anything related to preprocessing (-I, -D....)
	  CPP         C preprocessor command
	  CXX         C++ compiler command
	  CXXFLAGS    C++ compiler flags, see CFLAGS
	  CXXCPP      C++ preprocessor command
	  F77         Fortran 77 compiler command
	  FFLAGS      Fortran 77 compiler flags
	
	  //see man ld or whatever linker you're using
	  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
	              nonstandard directory <lib dir>
	  STRIP       Strip command
	
	  //see man pkg-config
	  //it's not recommanded to use pkg-config/libtool due to the troubles 
	  //introduced when crosscompiling/moving pakages from a test directory
	  //to a standard directory. the maintainers of those packages have never
	  //crosscompiled a thing or so.
	  PKG_CONFIG_PATH
	  PKG_CONFIG_DEBUG_SPEW
	  PKG_CONFIG_DISABLE_UNINSTALLED
	  PKG_CONFIG_ALLOW_SYSTEM_CFLAGS
	  PKG_CONFIG_ALLOW_SYSTEM_LIBS
	  PKG_CONFIG_LIBDIR
	
	
	  Use these variables to set a VALID and CORRECT developement environnement

	EOF
	local cur_pos=1
	echo options for this package
	echo
	while [ ${cur_pos} -le ${PACKAGE_OPTS_COUNT} ]; do
		format_option ${CONFIGURE_OPTS[$cur_pos]} 
		cur_pos=$(($cur_pos + 1))
	done

}

find_topsrc_objdir() {

    echo "${TEST_SEPARATOR}"
	reduce_name() {
		while [ "$#" -gt 0 ]; do
			if [ "$2" == ".." ]; then
				shift;
			elif [ "$1" != "." ]; then
				REDUCED_COMMAND="${REDUCED_COMMAND}/${1}"
			fi
			shift
		done
		REDUCED_COMMAND=${REDUCED_COMMAND/\/\//\/}
	}
	
	echo >&2

	local confpath=${confiserie/*\//}
	local name=${0/*\//}
	if echo $0 | grep -q "^/"; then
		TOPSRC_DIR=${0/$name/} 
	else
		TOPSRC_DIR=$PWD/${0/$name/}
	fi
	OLDIFS=$IFS
	IFS=$'/'
 	reduce_name $TOPSRC_DIR	
	IFS=$OLDIFS
	TOPSRC_DIR=$REDUCED_COMMAND

	OBJDIR=$PWD
	conf_cache TOPSRC_DIR
	conf_cache OBJDIR

	confiserie=$TOPSRC_DIR/$confpath
	conf_cache confiserie

	. ${confiserie}/create_link_farm.sh
}

run_init() {
    echo "${TEST_SEPARATOR}"
    echo "welcome to confiserie configure system" 1>&2
    echo "package configured with : " 1>&2
    parse_opts "$@"
    echo "confiserie init success" 1>&2
}

finish_confiserie() {
    echo "${TEST_SEPARATOR}"
	cat <<-EOF
	configured type 
	make to build
	make debug to build with debug
	make clean to clean (leave configuration information)
	make distclean to clean everything
	EOF
    echo "===========SUMMARY=============="
    for variable in ${MODIFIED_ENV}; do
        eval echo "export ${variable}=\\\"\$${variable}\\\"" 1>&2;
    done
    echo "configure success"
    exit 0
}

create_include() {
        File=${1};
        shift;
        while [ "$#" -gt 0 ]; do
                eval echo "export ${1}=\\\"\$${1}\\\"" >> ${File};
                shift;
        done
}

create_makefile() {
        File=${1};
        shift;
        for variable in ${MODIFIED_ENV}; do
                eval echo "export ${variable}=\$${variable}" >> ${File};
        done
        while [ "$#" -gt 0 ]; do
                eval echo "export ${1}=\$${1}" >> ${File};
                shift;
        done
}


clean_on_sig() {
    declare -F custom_clean_on_sig > /dev/null && 
    custom_clean_on_sig;
    exit 1
}


include() {
    return 0
}

declare -F custom_clean_on_sig > /dev/null && 
typeset -x custom_clean_on_sig

trap clean_on_sig 2 15                   &&
unalias -a                               &&
custom_clean_on_sig

. ${confiserie}/common_test_definition.sh
. ${confiserie}/clear_nls.sh || exit 1

if which_result=$(${confiserie}/which.sh which); then
    export WHICH=${which_result}
else
    export WHICH="${confiserie}/which.sh"
fi   &&
runtest ${confiserie}/confiserie.cache.functions.sh &&
run_init "$@"                                 &&
find_topsrc_objdir                            &&
runtest ${confiserie}/plateform_information.sh      &&
runtest ${confiserie}/tools/test_echo.sh            &&
runtest ${confiserie}/setup_dirs.sh                 &&
runtest ${confiserie}/tools/test_awk.sh
conf_cache WHICH
conf_cache confiserie

