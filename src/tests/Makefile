.SUFFIXES: .cpp
include ../conf.mk

#for sgi   -- comment out the lines below to use on HP
#CC=CC -g0 -o32
#CC=gcc

# Compiler options
OPTS+=-g
OPTS+=-O0
#OPTS+=-O2
OPTS+=-DDEBUG=1

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
CXX       = g++
CPPFLAGS += $(OPTS) -Wall -pedantic
endif

#######################################

CPPFLAGS += -I../ -I../include $(OPTS)

LIBGLUI = -L../lib -lglui
LIBGL   = -lGLU -lGL
LIBS    = -lXmu -lXext -lX11 -lXi -lm

# One of the following options only...

# (1) OpenGLUT
# LIBGLUT   = -L/usr/X11R6/lib -lopenglut
# CPPFLAGS += -I/usr/X11R6/include -DGLUI_OPENGLUT

# (2) FreeGLUT
# LIBGLUT   = -L/usr/X11R6/lib -lfreeglut
# CPPFLAGS += -I/usr/X11R6/include -DGLUI_FREEGLUT

# (3) GLUT
LIBGLUT   = -L/usr/X11R6/lib -lglut
CPPFLAGS += -I/usr/X11R6/include

GLUI_HEADERS = $(shell find ../include -type f)

#######################################


GLUI_LIB = ../lib/libglui.a

GLUI_TESTS = checkbox statictext


.PHONY: all setup examples tools clean depend doc doc-pdf doc-dist dist

all: $(GLUI_LIB) ${GLUI_TESTS}


examples: $(GLUI_EXAMPLES)

tools: $(GLUI_TOOLS)


${GLUI_TESTS}: $(addsuffix .cpp,${GLUI_TESTS}) $(GLUI_LIB)
	$(CXX) $(CPPFLAGS) -o $@ $(addsuffix .cpp,$@)  $(GLUI_LIB) $(LIBGLUT) $(LIBGL) $(LIBS)


.cpp.o: ${GLUI_HEADERS}
	$(CXX) $(CPPFLAGS) -c $<

.c.o: ${GLUI_HEADERS}
	$(CXX) $(CPPFLAGS) -c $<


clean:
	rm -f *.o $(addsuffix ${EXE},$(GLUI_TESTS))



