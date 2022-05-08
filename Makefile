# NOTES:
# * The `-g` flag is not really needed: `-Wl,--export-dynamic` alone will suffice
# * The -`finstrument-functions-exclude-file-list` option can be used
#   to exclude entire files from instrumentation

# ------------------------------------------------------------------------------

CXX      ?= g++
CXXFLAGS := -std=c++11 -O2 -g -Wl,--export-dynamic -finstrument-functions

LDFLAGS  :=

SOURCES := \
	src/extern.c \
	src/main.cc \
	src/member.cc \
	src/throw.cc \
	src/trace.c

# ------------------------------------------------------------------------------

example:
	$(CXX) -o example.out $(CXXFLAGS) $(LDFLAGS) $(SOURCES)
