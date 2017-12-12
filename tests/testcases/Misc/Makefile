# Misc testcases Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Werror -Wall -c -DAVOID_MEANINGFUL_CHECK -I../../../../googletest/googletest/include -I../../..

include objects.mk

all: $(MISC_TESTCASES_OBJECTS)

gpg-compatible: CXXFLAGS += -DGPG_COMPATIBLE
gpg-compatible: all

debug: CXXFLAGS += -g
debug: all

gpg-debug: CXXFLAGS += -DGPG_COMPATIBLE
gpg-debug: debug

.PHONY: clean

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(MISC_TESTCASES_OBJECTS)
