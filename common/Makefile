# common Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Werror -Wall -c -DAVOID_MEANINGFUL_CHECK

include objects.mk

all: $(COMMON_OBJECTS)

gpg-compatible: CXXFLAGS += -DGPG_COMPATIBLE
gpg-compatible: all

debug: CXXFLAGS += -g
debug: all

gpg-debug: CXXFLAGS += -DGPG_COMPATIBLE
gpg-debug: debug

.PHONY: clean

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(COMMON_OBJECTS)
