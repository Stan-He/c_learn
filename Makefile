CC=g++
SRCS=hellowworld.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=hello

start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

.cpp.o:
	$(CC) -o $@ -c $< -DMYLINUX


clean :
	rm -rf $(OBJS)