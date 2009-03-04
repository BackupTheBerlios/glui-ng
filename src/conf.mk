OS=$(shell uname -o)

ifeq (${OS},Cygwin)
   EXE:=.exe
endif

BackEnd = GLUT

.SECONDARY:


