# (C) 2005-2005 MALET Jean-Luc aka cityhunter
#this file is provided under the thermes of the BSD licence, you can use it, modify it
#include it into your commercial software as you want

# as a general rule to avoid issues
#    make variables first
#    make rules following (first appearing rule is the default when issuing 'make')
#    includes last


#general variables
.PHONY : all lib clean debug tests

export TOPSRC_DIR?=${PWD}
export VPATH=${TOPSRC_DIR}/${MSGSUBDIR}
include ${TOPSRC_DIR}/Makefile.confiserie

#default  target :
all :

#addition to environnement variable, be carefull when nesting subdirs in this makefile
LDFLAGS  += -lpthread
CFLAGS   += -Wall -fPIC -Werror-implicit-function-declaration
CPPFLAGS += -I../include -I./
ARFLAGS   =

########################################################################################
#here goes your sources :
BackEnd = GLUT


LIBGLUI = -L./lib -lglui
LIBS    = -lXext -lX11 -lm

# One of the following options only...

# (1) OpenGLUT
# LIBGLUT   = -L/usr/X11R6/lib -lopenglut
# CPPFLAGS += -I/usr/X11R6/include -DGLUI_OPENGLUT

# (2) FreeGLUT
# LIBGLUT   = -L/usr/X11R6/lib -lfreeglut
# CPPFLAGS += -I/usr/X11R6/include -DGLUI_FREEGLUT

# (3) GLUT
LIBGLUT   = -L/usr/X11R6/lib -lglut -L/bin
CPPFLAGS += -I/usr/X11R6/include


lib_LIBRARIES += libglui

libglui_SOURCES = $(shell find  -maxdepth 1 -regex '.*\.cpp\|.*\.c' -printf '%f\n')
ifeq (${BackEnd},XGL)
libglui_SOURCES+= $(shell find XGL -maxdepth 1 -regex '.*\.cpp\|.*\.c' )
endif
ifeq (${BackEnd},GLUT)
libglui_SOURCES+= $(shell find GLUT -maxdepth 1 -regex '.*\.cpp\|.*\.c' )
endif
ifeq (${BackEnd},WGL)
libglui_SOURCES+= $(shell find WGL -maxdepth 1 -regex '.*\.cpp\|.*\.c' )
endif

libglui_LDADD   =  -lGLU -lGL ${LIBGLUT}
#########################################################################################


#a special target : it only modify CFLAGS variables before making it the standard way
debug : CFLAGS+= -g3 -gdwarf-2 -O0
debug : all
	
clean : 
	${CLEANINGMSG} ${MSGSUBDIR}


#includes
include ${confiserie}/CXX/Makefile.auto_headers_deps
include ${confiserie}/Makefiles/Makefile.autolib
include ${confiserie}/CXX/Makefile.beautifull_rules

