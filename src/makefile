.SUFFIXES: .cpp

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

GLUI_HEADERS = $(shell find include -type f)

#######################################

GLUI_OBJS = glui_container.o glui_string.o glui.o glui_bitmap_img_data.o glui_bitmaps.o glui_button.o glui_edittext.o glui_commandline.o glui_checkbox.o glui_node.o glui_radio.o glui_statictext.o glui_panel.o glui_separator.o glui_spinner.o glui_control.o glui_splitter.o glui_translation.o glui_rotation.o glui_mouse_iaction.o glui_listbox.o glui_rollout.o glui_window.o arcball.o algebra3.o quaternion.o viewmodel.o glui_treepanel.o glui_tree.o glui_textbox.o glui_scrollbar.o glui_list.o glui_filebrowser.o glui_debug.o

GLUI_LIB = lib/libglui.a

GLUI_EXAMPLES = bin/example1 bin/example2 bin/example3 bin/example4 bin/example5 bin/example6

GLUI_TOOLS = bin/ppm2array

.PHONY: all setup examples tools clean depend doc doc-pdf doc-dist dist

all: setup $(GLUI_LIB) examples tools

setup:
	mkdir -p bin
	mkdir -p lib

examples: $(GLUI_EXAMPLES)

tools: $(GLUI_TOOLS)

bin/ppm2array: tools/ppm2array.cpp tools/ppm.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^

bin/%: example/%.cpp $(GLUI_LIB)
	$(CXX) $(CPPFLAGS) -o $@ $<  $(LIBGLUI) $(LIBGLUT) $(LIBGL) $(LIBS)

$(GLUI_LIB): $(GLUI_OBJS)
	ar -r $(GLUI_LIB) $(GLUI_OBJS)

${GLUI_OBJS}: ${GLUI_HEADERS}

.cpp.o: ${GLUI_HEADERS}
	$(CXX) $(CPPFLAGS) -c $<

.c.o: ${GLUI_HEADERS}
	$(CXX) $(CPPFLAGS) -c $<

docs:
	doxygen doc/doxygen.cfg

clean:
	rm -f *.o $(GLUI_LIB) $(GLUI_EXAMPLES) $(GLUI_TOOLS) 
	rm -fr doc/doxygen

DIST = glui-2.35

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
