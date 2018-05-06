#top makefile for athena
.PHONY:clean

CC = gcc
LD = gcc 
CXX = g++
CFLAGS = -c -O2 -Wall -I$(COMMON_INCLUDE) -I$(OS_INCLUDE)
LDFLAGS = -lpthread -lrt
CXXFLAGS =

TOP_PATH = $(shell pwd)
APP_NAME = bin/unitest

COMMON_INCLUDE = include/common
OS_INCLUDE = include/os

APP_SRC_PATH = apps/unitest
ATHENA_SRC_PATH = athena
COMMON_SRC_PATH = common
OS_SRC_PATH = os/linux
UTILS_SRC_PATH = utils

ALL_SRC_PATH = $(APP_SRC_PATH) $(ATHENA_SRC_PATH) $(COMMON_SRC_PATH) $(OS_SRC_PATH) $(UTILS_SRC_PATH)
ALL_SOURCES = $(foreach dir, $(ALL_SRC_PATH), $(wildcard $(dir)/*.c))
ALL_OBJECTS = $(patsubst %.c, objects/%.o, $(ALL_SOURCES))

ALL_SOURCES_DIR = $(sort $(dir $(ALL_SOURCES)))
ALL_OBJECTS_DIR = $(sort $(dir $(ALL_OBJECTS)))

DEP = $(ALL_OBJECTS:%.o=%.d)

$(APP_NAME):$(ALL_OBJECTS)
	$(LD) $^ -o $@ $(LDFLAGS)
	
-include $(DEP)

#$(ALL_OBJECTS) : $(ALL_SOURCES)
objects/%.o : %.c
	@mkdir -p $(sort $(dir $(ALL_OBJECTS)))
	$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(ALL_OBJECTS)
	rm -rf $(DEP)
	rm -rf $(APP_NAME)