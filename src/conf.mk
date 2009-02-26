OS=$(shell uname -o)

ifeq (${OS},Cygwin)
   EXE:=.exe
endif

.SECONDARY:


