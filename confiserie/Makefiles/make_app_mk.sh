#!/bin/sh
# $1 : install directory
# $2 : target
# $3 : var compilateur (CC, CXX, JAVAC....)

#/***********************************************************************
#* copyright (c) 2004-2006 MALET Jean-luc aka cityhunter
#* This library is free software; you can redistribute it and/or modify
#* it under the terms of the LGPL v2.1 or latter at your option
#* http://www.gnu.org/copyleft/lesser.html
#************************************************************************/


. ${confiserie}/format_name.sh
name=$( format_name "$2")
name="${name}${EXE}"

if test -n "${CONFISERIE_DEBUG}"; then
        echo generating GENERATED/${name}.${3}.d >&2
        echo \${1} : ${1} >&2
        echo \${2} : ${2} >&2
        echo \${3} : ${3} >&2
fi

cmd="\${${3}}  -o \$@ \$^ \${${3}_LDFLAGS} \${${name}_LDADD} "

case $1 in
	BIN_DIR)
		defaultmode="BIN_INSTALL_MODE:=755"
		defaultown="BIN_INSTALL_OWNER:=\$\${UID}";;
	SBIN_DIR)
		defaultmode="SBIN_INSTALL_MODE:=755"
		defaultown="SBIN_INSTALL_OWNER:=\$\${UID}";;
	CUSTOM_BIN_DIR)
		defaultmode="CUSTOM_BIN_INSTALL_MODE:=755"
		defaultown="CUSTOM_BIN_INSTALL_OWNER:=\$\${UID}";;
	*)	
		defaultown="NOINST_INSTALL_OWNER:=root"
		defaultmode="NOINST_INSTALL_MODE:=700"
esac


mkdir -p GENERATED
cat > GENERATED/${name}.${3}.d <<EOF
ifdef ${3}

ifdef ${name}_SOURCES

all : GENERATED/${name}
clean : clean_${name}
install : all install_${name}

GENERATED/${name} : \$(addsuffix .o, \$(addprefix GENERATED/, \$(basename \${${name}_SOURCES}))) \${${name}_ARADD}
	\${LDMESG} \$@
	rm -f \$@
	${cmd}	
	\${SUCCESSMSG} \$@


clean_${name} :
	\${CLEANINGMSG} GENERATED
	rm -rf GENERATED

-include \${${name}_SOURCES:%=GENERATED/%.d}
else
install :${name}_install

endif

ifdef $1

install_${name} : defaultmode=\$\${$defaultmode}
install_${name} : defaultown=\$\${$defaultown}
install_${name} :
	\${INSTALLMSG} GENERATED/${name} in \${$1}
	rm -f \${$1}/${name}
	mkdir -p \${$1}
	cp GENERATED/${name} \${$1}/${name}
	newmode=\${${name}_MODE}; chmod "\$\${newmode:=\${defaultmode}}" \${$1}/${name}
	newown=\${${name}_OWNER}; chown "\$\${newown:=\${defaultown}}" \${$1}/${name}
	\${confiserie}/Makefiles/make_lib_links.sh \${$1}/${name}
else
install_${name} :
	echo \${INSTALLMSG} ${name} $1 not defined... skipping install
endif


else 

${name} : 
	echo ${3} variable is not defined.... aborting
	exit 1

endif
EOF
echo GENERATED/${name}.${3}.d
