BUILD_FOLDER=./target
SRCS=./src/hashtable.c
MAIN=./src/main.c
NAME=$(BUILD_FOLDER)/hash.a
BIN=$(BUILD_FOLDER)/hash
OBJS=$(patsubst ./src/%.c, $(BUILD_FOLDER)/%.o,$(SRCS))
CC=cc
INCLUDE=-I./include
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb
AR=ar rsc
RM=rm -rf

all: prep $(NAME) main
$(BUILD_FOLDER)/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
main: $(NAME)
	$(CC) $(CFLAGS) $(MAIN) $(NAME) -o $(BIN)
prep:
	mkdir -p $(BUILD_FOLDER)
$(NAME): $(OBJS)
	$(AR) $@ $?
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus
