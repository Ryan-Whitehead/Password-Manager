#include directories
WORKING_DIR = ./

#Add each subfolder as include directories 
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2
LDFLAGS = -lcrypto 

PROG ?= main

# Main program objects 
MAIN_OBJS = main.o
#Submitted objects
SUBMITTED_OBJS = \
	$(WORKING_DIR)/pwManager.o
OBJS = $(MAIN_OBJS) $(SUBMITTED_OBJS)

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(PROG) *.o *.out *.txt \
	$(WORKING_DIR)/*.o

rebuild: clean mainprog