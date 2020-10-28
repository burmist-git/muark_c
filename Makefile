# Date        : Mon Oct 26 10:47:24 CET 2020
# Autor       : Leonid Burmistrov
# Description : 

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

CXX         = g++
CXX        += -I./     

CXXFLAGS    = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS   += $(ROOTCFLAGS)
CXXFLAGS   += $(ROOTLIBS)
CXXFLAGS   += $(ROOTGLIBS)
CXXFLAGS   += $(ROOTLDFLAGS)

#----------------------------------------------------#

all: convert2root convertWaveform2root

convert2root: convert2root.cc
	$(CXX) -o convert2root convert2root.cc $(CXXFLAGS)

convertWaveform2root: convertWaveform2root.cc
	$(CXX) -o convertWaveform2root convertWaveform2root.cc $(CXXFLAGS)

clean:
	rm -f convert2root
	rm -f convertWaveform2root
	rm -f *~
