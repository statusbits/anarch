# Anarch build script for mingw platform.

PLATFORM_DIR = ports/$(PLATFORM)

EXE_FILE = $(PLATFORM_DIR)/anarch

CC = gcc

CFLAGS =\
 -I.\
 -I$(PLATFORM_DIR)\
 -std=c99\
 -pedantic\
 -O3\
 -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers

LDFLAGS = -lGdi32

C_FILES	= $(wildcard $(PLATFORM_DIR)/*.c)

# ----- MAKE Rules -----------------------------------------------------------

all: $(EXE_FILE)

$(EXE_FILE):
	$(CC) $(CFLAGS) $(C_FILES) -o $@ $(LDFLAGS)

clean:
	rm $(EXE_FILE)
