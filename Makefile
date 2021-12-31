# compiler
CC = gcc
# compiler flags
CFLAGS = -ggdb -g -Wall -Wextra -Wmissing-prototypes -I ../posix_spawn

# name of executable target
TARGET = cash

# object files that correspond to a c file
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
# object files from harness already compiled
GIVEN_OBJS =

# header files
HEADERS = $(wildcard *.h)

.PHONY:
all: $(TARGET)

# .PHONY:
# assemble: $(TARGET)

# link object files to binary
# $@ means current target
# $^ means all dependencies
$(TARGET): $(OBJS) $(GIVEN_OBJS)
	$(CC) -Wall $^ -o $@

# complie and assemble c source and header files to object files
# $@ means current target
# $< means first dependency (c source file)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


# delete generated object files and target executable
.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f vlog.txt


