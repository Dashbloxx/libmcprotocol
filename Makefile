CC := gcc
CFLAGS := -Wall -Wextra -Iinclude
LDFLAGS :=
AR := ar
ARFLAGS := rcs

SRC_DIR := source

SRCS := $(wildcard $(SRC_DIR)/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)%.o,$(SRCS))

LIB := libmcprotocol.a

.PHONY: all clean

all: $(LIB)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIB)
