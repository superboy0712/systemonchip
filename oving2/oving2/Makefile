CC     = g++
OPT    = -O3
DEBUG  = -g
SYSTEMC_HOME = /usr/local/systemc-2.3.0/obj/
OTHER  = -Wno-deprecated -fpermissive -lsystemc -L$(SYSTEMC_HOME)/lib-linux64 -i$(SYSTEM_HOME)/include 
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)

MODULE = run
SRCS = button.cpp control.cpp top.cpp
OBJS = $(SRCS:.cpp=.o)

all: run.x

button.o: if.h button.h button.cpp

control.o: if.h control.h control.cpp

topp.o: button.h control.h top.cpp


