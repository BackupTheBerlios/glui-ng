#!/bin/sh
# $1 : install directory
# $2 : target
# $3 : extension


#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/

. ${confiserie}/format_name.sh
name=$( format_name "$2")

if test -n "${CONFISERIE_DEBUG}"; then
        echo generating GENERATED/${without_version_name}.d >&2
        echo \${1} : ${1} >&2
        echo \${2} : ${2} >&2
        echo \${3} : ${3} >&2
fi



LIB_INSTALL_MESSAGE_LD="don't forget to run ldconfig or to update LD_LIBRARY_PATH env variable"


case $1 in
	LIB_DIR)
		defaultmode="LIB_INSTALL_MODE:=755"
		defaultown="LIB_INSTALL_OWNER:=\$\${UID}";;
	LIBEXEC_DIR)
		defaultmode="LIBEXEC_INSTALL_MODE:=755"
		defaultown="LIBEXEC_INSTALL_OWNER:=\$\${UID}";;
	CUSTOM_LIB_DIR)
		defaultmode="CUSTOM_LIB_INSTALL_MODE:=755"
		defaultown="CUSTOM_LIB_INSTALL_OWNER:=\$\${UID}";;
	*)
		defaultown="NOINST_INSTALL_OWNER:=root"
		defaultmode="NOINST_INSTALL_MODE:=700"
esac


version=$(eval echo ${name}_VERSION)
complete_name="${2}-\${${version}}${3}"
without_version_name="${2}${3}"

if [ "${3}" == ".so" ]; then
	cmd="\${LD} \${LDFLAGS} \${${name}_LDADD} -shared -Bdynamic -soname \$@ -o \$@ \$^ \${${name}_ARADD} "
elif [ "${3}" == ".dll" ]; then
        cmd="\${CC} \${CC_LDFLAGS} -shared \
                -o \$@ -Wl,--out-implib=\$@.a\
                -Wl,--export-all-symbols -Wl,--enable-auto-import \
                -Wl,--no-whole-archive  \${${name}_LDADD} \$^ \${${name}_ARADD}"
elif [ "${3}" == ".a" ]; then
	cmd="\${AR} r \${ARFLAGS} \$@ \$^ \${${name}_ARADD} && \${RANLIB} \$@"
fi

mkdir -p GENERATED
cat > GENERATED/${without_version_name}.d <<EOF
ifndef LD
\$(error LD is undefined)
endif

ifdef LD

ifdef CONFISERIE_DEBUG
\$(warning LD : \${LD})
\$(warning AR : \${AR})
\$(warning LDFLAGS : \${LDFLAGS})
\$(warning ARFLAGS : \${ARFLAGS})
\$(warning ${name}_LDADD : \${${name}_LDADD})
\$(warning ${name}_ARADD : \${${name}_ARADD})
\$(warning ${name}_MODE : \${${name}_MODE})
\$(warning ${name}_OWNER :\${${name}_OWNER})
endif


all : GENERATED/${complete_name}
clean : clean_${complete_name}
install : all install_${complete_name}

GENERATED/${complete_name} : \$(addprefix GENERATED/, \$(addsuffix .o, \$(basename \${${name}_SOURCES}))) \${${name}_ARADD}
	\${LDMESG} \$@
	rm -f \$@
	${cmd}
	\${confiserie}/Makefiles/make_lib_links.sh \${$1}/${complete_name}
	\${SUCCESSMSG} \$@


clean_${complete_name} :
	\${CLEANINGMSG} GENERATED
	rm -rf GENERATED

ifdef $1

install_${complete_name} : defaultmode=\$\${$defaultmode}
install_${complete_name} : defaultown=\$\${$defaultown}
install_${complete_name} :
	\${INSTALLMSG} GENERATED/${complete_name} in \${$1}
	rm -f \${$1}/${complete_name}
	mkdir -p \${$1}
	cp GENERATED/${complete_name} \${$1}/${complete_name}
	newmode=\${${name}_MODE}; chmod \$\${newmode:=\${defaultmode}} \${$1}/${complete_name}
	newown=\${${name}_OWNER}; chown "\$\${newown:=\${defaultown}}" \${$1}/${complete_name}
	\${confiserie}/Makefiles/make_lib_links.sh \${$1}/${complete_name}
	echo "${LIB_INSTALL_MESSAGE_LD}"
else
install_${complete_name} :
	echo \${INSTALLMSG} ${complete_name} : $1 not defined... skipping install
endif
	
-include \${${name}_SOURCES:%=GENERATED/%.d}

else 

GENERATED/${complete_name} : 
	echo LD variable is not defined.... aborting
	exit 1

endif
EOF
echo GENERATED/${without_version_name}.d
