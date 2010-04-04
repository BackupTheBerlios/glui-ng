# (C) 2005-2005 MALET Jean-Luc aka cityhunter
#this file is provided under the thermes of the BSD licence, you can use it, modify it
#include it into your commercial software as you want

# as a general rule to avoid issues
#    make variables first
#    make rules following (first appearing rule is the default when issuing 'make')
#    includes last


#general variables
.PHONY : all lib clean tests

export TOPSRC_DIR?=..

# load configuration (variables with gnu make Makefile are modified chronologicaly
# ie when they appears in a Makefile)
include ${TOPSRC_DIR}/Makefile.confiserie

#if you want to setup a VPATH
export VPATH=${TOPSRC_DIR}/${MSGSUBDIR}

#default target (make execute by defaut the first target he find):
all :

ifeq (${DebugBuild},yes)
CXXFLAGS+= -g3 -gdwarf-2 -O0
endif

ifeq (${BackEnd},XGL)
CXXFLAGS+= -D__USE_XLIB
BACKENDLIB =
endif
ifeq (${BackEnd},GLUT)
CXXFLAGS+= -D__USE_GLUT
BACKENDLIB = -lglut
endif
ifeq (${BackEnd},WGL)
CXXFLAGS+= -D__USE_WIN32
endif


ifneq (${SHAREDLIBEXT},)
LIBGLUIDLL = -L../src/GENERATED/ -lglui-${libglui_VERSION}
else
LIBGLUIA = ../src/GENERATED/libglui-*.a
endif

#addition to environnement variable, be carefull when nesting subdirs in this makefile
CXX_LDFLAGS  += -lpthread -lGLU -lGL
CXXFLAGS   += -Wall -fPIC
CPPFLAGS += -I../include

noinst_CXXPROGRAMS=
#tests that aren't expected to build... (compilation step safety)
#noinst_CXXPROGRAMS+= NonCopyable
NonCopyable_SOURCES = NonCopyable.cpp

# programs to install in ${prefix}/bin directory
# this variable is used in Makefile.autoapp to create the required Makefiles
# it then has to be set before including of Makefiles.autoapp
noinst_CXXPROGRAMS+= SizeComputationTest PackingTest ContainerEventTest
noinst_CXXPROGRAMS+= WindowTest KeyboardTest VertexObjectTest
noinst_CXXPROGRAMS+= SmartPointerTest ButtonTest EventInterpreterTest
#noinst_CXXPROGRAMS+= Lightning_test


#sources and additional variables for myapp1
SizeComputationTest_SOURCES = SizeComputationTest.cpp
SizeComputationTest_LDADD   = ${LIBGLUIDLL}  ${BACKENDLIB}
SizeComputationTest_ARADD   = ${LIBGLUIA}

PackingTest_SOURCES = PackingTest.cpp
PackingTest_LDADD   = ${LIBGLUIDLL}  ${BACKENDLIB}
PackingTest_ARADD   = ${LIBGLUIA}

ContainerEventTest_SOURCES = ContainerEventTest.cpp
ContainerEventTest_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
ContainerEventTest_ARADD   = ${LIBGLUIA}

WindowTest_SOURCES = WindowTest.cpp
WindowTest_LDADD   = ${LIBGLUIDLL}  ${BACKENDLIB}
WindowTest_ARADD   = ${LIBGLUIA}

KeyboardTest_SOURCES = KeyboardTest.cpp
KeyboardTest_LDADD   = ${LIBGLUIDLL}  ${BACKENDLIB}
KeyboardTest_ARADD   = ${LIBGLUIA}

Lightning_test_SOURCES = Lightning_test.cpp
Lightning_test_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
Lightning_test_ARADD   = ${LIBGLUIA}

VertexObjectTest_SOURCES = VertexObjectTest.cpp
VertexObjectTest_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
VertexObjectTest_ARADD   = ${LIBGLUIA}

SmartPointerTest_SOURCES = SmartPointer_test.cpp
SmartPointerTest_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
SmartPointerTest_ARADD   = ${LIBGLUIA}

ButtonTest_SOURCES = button.cpp
ButtonTest_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
ButtonTest_ARADD   = ${LIBGLUIA}

EventInterpreterTest_SOURCES = EventInterpreter.cpp
EventInterpreterTest_LDADD   = ${LIBGLUIDLL}   ${BACKENDLIB}
EventInterpreterTest_ARADD   = ${LIBGLUIA}


clean : 
	${CLEANINGMSG} ${MSGSUBDIR}


#includes
include ${confiserie}/CXX/Makefile.autoapp
include ${confiserie}/CXX/Makefile.beautifull_rules
include ${confiserie}/CXX/Makefile.auto_headers_deps


