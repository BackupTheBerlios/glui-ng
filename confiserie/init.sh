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

##CONFIGURE_OPTS --prefix= PREFIX "configure package to be located in prefix" "path" /usr/local
##CONFIGURE_OPTS --crosscompiling= CROSSCOMPILING "the package is crosscompiled" "YES NO" NO
##CONFIGURE_OPTS --enable-link-farm= ENABLE_LINK_FARM "enable link farm creation" "YES NO" NO

interactive_conf() {
	ask_user() {
                option=$1
		var=$2
		default=$5
		printf " $1? ($3) [$4] default to $5\n"
		while read REPLY; do
			if [ -z "${REPLY}" ]; then
				printf "using default $5\n"
				REPLY="$5"
				break
			elif [ "$(printf "$4" | wc -w)" -le 1 ]; then
				break
			elif [ "$(printf "$4" | wc -w)" -gt 1 ] && printf "$4" | grep -q ${REPLY}; then
				break
			else
				printf " $1 need : $4\n"
			fi
                done
		eval $var=${REPLY}
		conf_cache $var
                CONFIGURE_LINE="${CONFIGURE_LINE} $option${REPLY}"
	}

	option_flags=$(cut -d ' ' -f 1  <${confiserie}/options| grep -v '^[[:space:]]*#.*')
	for opt in ${option_flags}; do
		eval ask_user $(grep -- ${opt} <${confiserie}/options)
	done
}

parse_opts() {
	assign_defaults() {
                option=$1
		var=$2
		default=$5
		is_allready_set=$(printf "${MODIFIED_ENV}" | grep $var)
		if [ -n "$default" ] && [ -z "${is_allready_set}" ]; then
			eval $var=$default
                        conf_cache $var
                        CONFIGURE_LINE="${CONFIGURE_LINE} $option$default"
		fi
	}

	read_vars() {
		long=$1
		var=$2
                possibilities=${4}
	}
	
        CONFIGURE_LINE="./configure"

        if [ -f "${confiserie}/options" ]; then
		option_flags=$(cut -d ' ' -f 1  <${confiserie}/options | grep -v '^[[:space:]]*#.*')


		while [  "$#" -gt 0 ]; do
				eval read_vars $(grep -- ${1%=*} <${confiserie}/options) 
				case $1 in
					-h|--help) display_help >&2; exit 0;;
					-V|--version*) printf "$0 : 0.0.2"; exit 0;;
					--interactive) interactive_conf;;
					$long*) 
						[ -z "$long" ] && printf "unknown option ${1%=*}\n" && return 1
						if [ "$(printf "$possibilities" | wc -w)" -gt 1 ]; then
							printf "$possibilities" | grep -q ${1##$long} ||
							{
								printf "$long need : $possibilities\n"
								exit 1;
							}
						fi
						eval export $var=${1##$long}; 
                                                CONFIGURE_LINE="${CONFIGURE_LINE} $1"
						conf_cache $var ;;
                                        *)
                                                printf "unknow option $1\n"
						return 1
						;;
				esac
			shift

		done
		for opt in ${option_flags}; do
			eval assign_defaults $(grep -- ${opt} <${confiserie}/options)
		done
                printf "configure line used : ${CONFIGURE_LINE}\n"
	fi
}

	

display_help() {

	format_option() {
		printf "\t$1\n\t\tresult in $2, $3, [$4] default:$5\n"
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
	  //it's not recommanded to use libtool due to the troubles 
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
	printf "options for this package\n\n"
	option_flags=$(cut -d ' ' -f 1  <${confiserie}/options| grep -v '^[[:space:]]*#.*')
	for opt in ${option_flags}; do
		eval format_option $(grep -- ${opt} <${confiserie}/options)
	done
}

find_topsrc_objdir() {
    printf "${TEST_SEPARATOR}init.sh${TEST_SEPARATOR}\n"
	reduce_name() {
		shift
		while [ "$#" -gt 0 ]; do
			if [ "$2" = ".." ]; then
				shift;
			elif [ "$1" != "." ]; then
				REDUCED_COMMAND="${REDUCED_COMMAND}/${1}"
			fi
			shift
		done
	}
	
	printf "\n"

	local confpath=${confiserie##*/}
	if printf "$0" | grep -q "^/"; then
		TOPSRC_DIR=${0%/*} 
	else
		TOPSRC_DIR=$PWD/${0%/*}
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
    printf "${TEST_SEPARATOR}init.sh${TEST_SEPARATOR}\n" &&
    printf "welcome to confiserie configure system\n"    &&
    printf "package configured with :\n"                 &&
    parse_opts "$@"                                      &&
    printf "confiserie init success\n"
}

finish_confiserie() {
    printf "${TEST_SEPARATOR}init.sh${TEST_SEPARATOR}\n"
	cat <<-EOF
	configured type 
	make to build
	make debug to build with debug
	make clean to clean (leave configuration information)
	make distclean to clean everything
	EOF
    printf "===========SUMMARY==============\n"
    for variable in ${MODIFIED_ENV}; do
        eval printf \'export ${variable}=\"%b\"\\n\' \$${variable} 1>&2;
    done
    printf "configure success\n"
    exit 0
}

create_include() {
        File=${1};
        shift;
        while [ "$#" -gt 0 ]; do
                eval printf \'export ${1}=\"%b\"\\n\' \$${1} >> ${File};
                shift;
        done
}

create_makefile() {
        File=${1};
        shift;
        for variable in ${MODIFIED_ENV}; do
                eval printf \'export ${variable}=%b\\n\' \$${variable}>> ${File};
        done
        while [ "$#" -gt 0 ]; do
                eval printf \'export ${1}=%b\\n\' \$${1} >> ${File};
                shift;
        done
}


clean_on_sig() {
    #declare -F custom_clean_on_sig > /dev/null && 
    custom_clean_on_sig;
    exit 1
}


include() {
    return 0
}

trap clean_on_sig 2 15                   &&
unalias -a                               &&
custom_clean_on_sig

. ${confiserie}/common_test_definition.sh
. ${confiserie}/clear_nls.sh || exit 1

printf "${TEST_SEPARATOR}init.sh${TEST_SEPARATOR}\nchecking for which "
if which_result=$(${confiserie}/which.sh which); then
    export WHICH=${which_result}
else
    export WHICH="${confiserie}/which.sh"
fi   &&
conf_cache WHICH                                    &&
runtest ${confiserie}/tools/test_echo.sh            &&
run_init "$@"                                 &&
find_topsrc_objdir                            &&
runtest ${confiserie}/plateform_information.sh      &&
runtest ${confiserie}/setup_dirs.sh                 &&
runtest ${confiserie}/tools/test_awk.sh

