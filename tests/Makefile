# (C) 2005-2005 MALET Jean-Luc aka cityhunter
#this file is provided under the thermes of the BSD licence, you can use it, modify it
#include it into your commercial software as you want

# as a general rule to avoid issues
#    make variables first
#    make rules following (first appearing rule is the default when issuing 'make')
#    includes last


#general variables
.PHONY : all lib clean debug tests

export TOPSRC_DIR?=..

# load configuration (variables with gnu make Makefile are modified chronologicaly
# ie when they appears in a Makefile)
include ${TOPSRC_DIR}/Makefile.confiserie

#if you want to setup a VPATH
export VPATH=${TOPSRC_DIR}/${MSGSUBDIR}

#default target (make execute by defaut the first target he find):
all :


ifneq (${SHAREDLIBEXT},)
LIBGLUIDLL = -L../src/GENERATED/ -lglui-${libglui_VERSION}
else
LIBGLUIA = ../src/GENERATED/libglui-*.a
endif

#addition to environnement variable, be carefull when nesting subdirs in this makefile
CXX_LDFLAGS  += -lpthread -lGLU -lGL
CXXFLAGS   += -Wall -fPIC
CPPFLAGS += -I../include

# programs to install in ${prefix}/bin directory
# this variable is used in Makefile.autoapp to create the required Makefiles
# it then has to be set before including of Makefiles.autoapp
noinst_CXXPROGRAMS = SizeComputationTest PackingTest ContainerEventTest
noinst_CXXPROGRAMS+= GlutWindowTest GlutKeyboardTest GlutKeyboardUserTest
#noinst_CXXPROGRAMS+= Lightning_test

#sources and additional variables for myapp1
SizeComputationTest_SOURCES = SizeComputationTest.cpp
SizeComputationTest_LDADD   = ${LIBGLUIDLL}  -lglut
SizeComputationTest_ARADD   = ${LIBGLUIA}

PackingTest_SOURCES = PackingTest.cpp
PackingTest_LDADD   = ${LIBGLUIDLL}  -lglut
PackingTest_ARADD   = ${LIBGLUIA}


ContainerEventTest_SOURCES = ContainerEventTest.cpp
ContainerEventTest_LDADD   = ${LIBGLUIDLL}  -lglut
ContainerEventTest_ARADD   = ${LIBGLUIA}


GlutWindowTest_SOURCES = GlutWindowTest.cpp
GlutWindowTest_LDADD   = ${LIBGLUIDLL} -lglut
GlutWindowTest_ARADD   = ${LIBGLUIA}


GlutKeyboardTest_SOURCES = GlutKeyboardTest.cpp
GlutKeyboardTest_LDADD   = ${LIBGLUIDLL}  -lglut
GlutKeyboardTest_ARADD   = ${LIBGLUIA}


GlutKeyboardUserTest_SOURCES = GlutKeyboardUserTest.cpp
GlutKeyboardUserTest_LDADD   = ${LIBGLUIDLL}  -lglut
GlutKeyboardUserTest_ARADD   = ${LIBGLUIA}


Lightning_test_SOURCES = Lightning_test.cpp
Lightning_test_LDADD   = ${LIBGLUIDLL}  -lglut
Lightning_test_ARADD   = ${LIBGLUIA}



#a special target : it only modify CFLAGS variables before making it the standard way
debug : CXXFLAGS+= -g3 -gdwarf-2 -O0
debug : all
	
clean : 
	${CLEANINGMSG} ${MSGSUBDIR}


#includes
include ${confiserie}/CXX/Makefile.autoapp
include ${confiserie}/CXX/Makefile.beautifull_rules
include ${confiserie}/CXX/Makefile.auto_headers_deps


