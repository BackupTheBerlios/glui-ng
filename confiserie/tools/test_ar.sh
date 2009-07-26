#!/bin/sh
#licenced under the GPL, taken from autoconf generated script

# Find a good install program.  We prefer a C program (faster),
# so one script is as good as another.  But avoid the broken or
# incompatible versions:
# SysV /etc/install, /usr/sbin/install
# SunOS /usr/etc/install
# IRIX /sbin/install
# AIX /bin/install
# AmigaOS /C/install, which installs bootblocks on floppy discs
# AIX 4 /usr/bin/installbsd, which doesn't work without a -g flag
# AFS /usr/afsws/bin/install, which mishandles nonexistent args
# SVR4 /usr/ucb/install, which tries to use the nonexistent group "staff"
# OS/2's system install, which has a completely different semantic
# ./install, which can be erroneously created by make from ./install.sh.
WHICH=${WHICH:=which}
confiserie=${confiserie:=..}
. ${confiserie}/confiserie.cache.functions.sh



mytest() {
  run_test() {
    if test -z "$AR" || test -z "$RANLIB"; then
			AR=${AR:=$(${WHICH} ar)}             &&
			RANLIB=${RANLIB:=$(${WHICH} ranlib)} 
		fi
  }

	run_test 
	printf "checking for an ar : "
	conf_cache AR
	printf "checking for a ranlib : "
	conf_cache RANLIB
	printf "checking for ARFLAGS : "
	conf_cache ARFLAGS

}

mytest
