# (C) 2005-2005 MALET Jean-Luc aka cityhunter
#this file is provided under the thermes of the BSD licence, you can use it, modify it
#include it into your commercial software as you want

# this is a Makefile that show how to use subdirectories
# subdirectories are stored in subdirs variable 


# as a general rule to avoid issues
#    make variables first
#    make rules following (first appearing rule is the default when issuing 'make')
#    includes last


.PHONY : all clean debug install distclean ${subdirs}
#default target
all :

MSGSUBDIR?=.

#prevent commands to be outputed,  run make -n to see exactly what is performed
#or comment this during developement
ifndef DEBUG
export MAKEFLAGS+=s
endif

#your subdirs
subdirs = lib drivers tests applications

all :  ${subdirs} runtest
all clean debug install : ${subdirs}
install debug : all
	
#your subdirs
Makefile.confiserie : ./configure
	./configure

# don't forget to rm .config.cache
distclean : 
	rm -f .config.cache
	rm Makefile.confiserie
	rm config.h

# special rule :: with nothing that follow tells make to rebuild the subdirs everytime
# this rules runs make on the subtree
# note the test -e lines used to create the tree dynamically when using VPATH
# and the use of VPATH variable when passing the relay to submake
# setting VPATH here prevent having to redefine it in each sub Makefiles
${subdirs} ::
	echo ${PWD}/$@/
	test -e $@ || mkdir -p $@
	test -e $@/Makefile || cp ${TOPSRC_DIR}/${MSGSUBDIR}/$@/Makefile $@/Makefile
	$(MAKE) $(MAKECMDGOALS) -C $@ MSGSUBDIR=${MSGSUBDIR}/$@/ VPATH=${TOPSRC_DIR}/${MSGSUBDIR}/$@
	echo ${PWD}


runtest :
	./test.sh 2>/dev/null

#includes
export TOPSRC_DIR?=${PWD}
include ${TOPSRC_DIR}/Makefile.confiserie


