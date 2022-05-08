# NOTES:
# * The `-g` flag is not really needed: `-Wl,--export-dynamic` alone will suffice
# * The -`finstrument-functions-exclude-file-list` option can be used
#   to exclude entire files from instrumentation

# ------------------------------------------------------------------------------

CXX      ?= g++
CXXFLAGS := -std=c++11 -O2 -g -Wl,--export-dynamic -finstrument-functions

LDFLAGS  :=

SOURCES := \
	src/main.cc \
	src/trace.c \
	src/test_funcs/extern.c \
	src/test_funcs/member.cc \
	src/test_funcs/throw.cc

# ------------------------------------------------------------------------------

example:
	$(CXX) -o example.out $(CXXFLAGS) $(LDFLAGS) $(SOURCES)
