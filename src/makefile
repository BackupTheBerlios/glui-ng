.SUFFIXES: .cpp

#comment this for verbose make
MAKEFLAGS+= -s

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

CPPFLAGS += -I./ -I./include $(OPTS)

LIBGLUI = -L./lib -lglui
LIBGL   = -lGLU -lGL
LIBS    = -lXext -lX11 -lm

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

GLUI_HEADERS = $(shell find include -type f)

#######################################
GLUI_SRC = $(shell find  -maxdepth 1 -regex '.*\.cpp\|.*\.c')
GLUI_OBJS = $(addprefix GENERATED/,$(addsuffix .o,$(basename ${GLUI_SRC})))

GLUI_LIB = GENERATED/lib/libglui.a

GLUI_TOOLS = GENERATED/bin/ppm2array

.PHONY: all setup examples tools clean depend doc doc-pdf doc-dist dist tests

all: $(GLUI_LIB) examples tools

$(GLUI_LIB) : setup
testplan : tests
	./tests/testplan.sh

tests : $(GLUI_LIB)
	make -C tests $@

setup:
	mkdir -p GENERATED
	mkdir -p GENERATED/bin
	mkdir -p GENERATED/lib

examples: $(GLUI_LIB)
	make -C example $@

tools: $(GLUI_TOOLS) $(GLUI_LIB)

GENERATED/bin/ppm2array: tools/ppm2array.cpp tools/ppm.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^

GENERATED/bin/%: example/%.cpp $(GLUI_LIB)
	$(CXX) $(CPPFLAGS) -o $@ $<  $(LIBGLUI) $(LIBGLUT) $(LIBGL) $(LIBS)

$(GLUI_LIB): $(GLUI_OBJS)
	ar -r $(GLUI_LIB) $(GLUI_OBJS)

${GLUI_OBJS}: ${GLUI_HEADERS}

GENERATED/%.o: %.cpp ${GLUI_HEADERS}
	echo "    [CXX] $<"
	$(CXX) $(CPPFLAGS) -c $< -o $@

GENERATED/%.o: %.c ${GLUI_HEADERS}
	echo "    [CC ] $<"
	$(CXX) $(CPPFLAGS) -c $< -o $@


docs:
	doxygen doc/doxygen.cfg

clean:
	rm -rf GENERATED
	rm -f $(GLUI_LIB) $(GLUI_TOOLS)
	rm -fr doc/doxygen
	make -C tests $@

DIST = glui-experiments2.35

doc:
	doxygen doc/doxygen.cfg

doc-pdf:
	cd doc/doxygen/latex &&	pdflatex refman.tex && pdflatex refman.tex && pdflatex refman.tex

doc-dist:
	mkdir -p $(DIST)/doc
	cp `find doc/doxygen/html -type f` $(DIST)/doc
	tar cv $(DIST) | gzip -9 - > $(DIST)-doc.tgz
	zip -vr9 $(DIST)-doc.zip $(DIST)
	rm -Rf $(DIST)
	
dist: clean
	mkdir -p $(DIST)
	cp --parents \
		`find -type f -name "*.cpp"` \
		`find -type f -name "*.c"` \
		`find -type f -name "*.h"` \
		`find -type f -name "*.dev"` \
		`find -type f -name "*.dsp"` \
		`find -type f -name "*.dsw"` \
		`find -type f -name "*.vcproj"` \
		`find -type f -name "*.sln"` \
		`find -type f -name "*.txt"` \
		makefile \
		$(DIST)
	tar cv $(DIST) | gzip -9 - > $(DIST).tgz
	rm -Rf $(DIST)

# DO NOT DELETE THIS LINE -- make depend depends on it.
