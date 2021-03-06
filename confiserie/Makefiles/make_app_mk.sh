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
        printf generating GENERATED/${name}.${3}.d >&2
        printf \${1} : ${1} >&2
        printf \${2} : ${2} >&2
        printf \${3} : ${3} >&2
fi

cmd="\${${3}} \${${3}FLAGS} \${CPPFLAGS} -o \$@ \${${name}_OBJ} \${${name}_ARADD} \${${3}_LDFLAGS} \${${name}_LDADD} "

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

ifdef CONFISERIE_DEBUG
\$(warning ${3}FLAGS : \${${3}FLAGS})
\$(warning CPPFLAGS : \${CPPFLAGS})
\$(warning ${3}_LDFLAGS : \${${3}_LDFLAGS})
\$(warning ${name}_SOURCES : \${${name}_SOURCES})
\$(warning ${name}_ARADD : \${${name}_ARADD})
\$(warning ${name}_LDADD : \${${name}_LDADD})
\$(warning ${name}_MODE : \${${name}_MODE})
\$(warning ${name}_OWNER :\${${name}_OWNER})
\$(warning ${name}_DEPEND :\${${name}_DEPEND})
\$(warning SUCCESSMSG :\${SUCCESSMSG})
endif

ifdef ${name}_SOURCES

MAKEFLAGS += Rr

all : GENERATED/${name}
clean : clean_${name}
install : all install_${name}

.PHONY : \${${name}_DEPEND}
GENERATED/${name} : \${${name}_DEPEND}

${name}_OBJ=\$(addsuffix .o, \$(addprefix GENERATED/, \$(basename \${${name}_SOURCES})))

GENERATED/${name} : \${${name}_OBJ} \${${name}_ARADD}
	\${LDMESG} \$@
	rm -f \$@
	${cmd}	
	\${SUCCESSMSG} \$@


clean_${name} :
	\${CLEANINGMSG} GENERATED
	rm -rf GENERATED

ifeq (${ENABLE_AUTODEPS}, yes)
ifneq (\${MAKECMDGOALS},clean)
-include \${${name}_SOURCES:%=GENERATED/%.d}
endif
endif

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
	printf \${INSTALLMSG} ${name} $1 not defined... skipping install
endif


else 

${name} : 
	printf ${3} variable is not defined.... aborting
	exit 1

endif
EOF
printf GENERATED/${name}.${3}.d
