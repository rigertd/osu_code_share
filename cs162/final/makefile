# Author:  David Rigert
# Created: 3/15/2015
# Final Project makefile

CXX = g++
DEBUG = -g
CXXFLAGS = -std=c++0x $(DEBUG)
PROGS = final test
OUTPUTS = 
FINALOBJS = BasicRoom.o Command.o ConditionRoom.o Item.o Player.o Room.o SwitchRoom.o World.o
TESTOBJS = UnitTest.o
MAINOBJS = final.o test.o
OBJS = $(FINALOBJS) $(TESTOBJS) $(MAINOBJS)

all: $(PROGS)

final: $(FINALOBJS) final.o
	$(CXX) $(CXXFLAGS) $(FINALOBJS) final.o -o $@

test: $(FINALOBJS) $(TESTOBJS) test.o
	$(CXX) $(CXXFLAGS) $(FINALOBJS) $(TESTOBJS) test.o -o $@

$(OBJS): $(@:.o=.cpp)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp)

clean:
	$(RM) $(PROGS) $(OBJS) $(OUTPUTS)
