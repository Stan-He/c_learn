CXX :=g++
SRCS=$(wildcard src/*.cpp)
SRCS += $(wildcard *.cpp)


OBJS=$(SRCS:.cpp=.o)

EXEC=hello
INCLUDE := -I $(CURDIR)/include

CFLAGS := -g -std=c++17 -W -Wall -Wfatal-errors
LDLIBS := 
LDFLAGS :=

.PHONY : all clean

all: $(EXEC) 

$(EXEC):    $(OBJS)  
	$(CXX) $(CFLAGS) $(INCLUDE) $(LDFLAGS)  -o $(EXEC) $(OBJS) $(LDLIBS)


%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<


clean :
	rm   $(EXEC) $(OBJS)