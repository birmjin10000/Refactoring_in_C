UNITY_ROOT=./Unity
C_COMPILER=gcc
CFLAGS = -Wall -O3 -std=c99 -pedantic-errors
TARGET_BASE=test
TARGET_EXTENSION=.out

TARGET = $(TARGET_BASE)$(TARGET_EXTENSION)
SRC_FILES=$(UNITY_ROOT)/src/unity.c $(wildcard src/*.c) $(wildcard src/**/*.c) test/*.c test/test_runners/TestMovieRental_Runner.c
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src
SYMBOLS=-DTEST

CLEANUP = rm -f build/*.o; rm -f $(TARGET)

all: clean default

default:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(TARGET)
	./$(TARGET)

clean:
	$(CLEANUP)
