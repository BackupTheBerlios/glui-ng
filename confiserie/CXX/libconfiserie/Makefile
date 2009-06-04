ifndef CONFISERIE_DEBUG
MAKEFLAGS += s
endif
noinst_LIBRARIES += libconfiserie
libconfiserie_SOURCES =  libconfiserie.cpp  libconfiserie2.cpp
libconfiserie_VERSION =  0.0.0

noinst_CXXPROGRAMS = testlibconfiserie
testlibconfiserie_SOURCES = testlibconfiserie.cpp
testlibconfiserie_LDADD   = -lconfiserie-0 -L./GENERATED
testlibconfiserie_DEPEND  = libconfiserie


include ${confiserie}/Makefiles/Makefile.autolib
include ${confiserie}/CXX/Makefile.autoapp
include ${confiserie}/CXX/Makefile.beautifull_rules

