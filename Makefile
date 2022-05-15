CFLAGS := -Wall -Wextra -Werror -g3 -fstack-protector -fsanitize=address
LIBS := -lcurses $(shell pkg-config --libs libgit2)
CC = g++
MAKEFLAGS += --no-print-directory

UNAME = $(shell uname -s)



_COLOR := \033[1;33m
_END := \033[0m

SRC_DIR := $(shell mkdir -p ./srcs && printf "./srcs")
BIN_DIR := $(shell mkdir -p ./bin && printf "./bin")
INC_DIR := $(shell mkdir -p ./include && printf "./include")
BUILD_DIR ?= ./build

INC_DIR += $(shell pkg-config --cflags libgit2)

NAME := vimacs

SRCS = $(shell find $(SRC_DIR) -name *.cpp)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.cpp.o : %.cpp
	@printf "[$(_COLOR)make$(_END)] compiling $@...\n"
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

$(NAME):
	@printf "[$(_COLOR)make$(_END)] checking update status...\n"
	@if ! $(MAKE) $(BIN_DIR)/$(NAME) | grep -v "is up to date" ; then \
		printf "[$(_COLOR)make$(_END)] $@ is up to date ✅\n"; \
	fi

$(BIN_DIR)/$(NAME):	$(OBJS) $(LIB_FILES)
	@printf "[$(_COLOR)make$(_END)] linking $@\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN_DIR)/$(NAME)

release: CFLAGS += -02 -march=native
release: fclean
release: all

tests: $(OBJS)
	@printf "[$(_COLOR)make$(_END)] starting tests...\n"
	@$(MAKE) -e TEST_FLAGS="$(TEST_FLAGS)" -e TEST_OBJ="$(OBJS)" -C $(TESTS_DIR)

all:
	@$(MAKE) $(NAME)

clean:
	@rm -rf $(BUILD_DIR)
	@printf "[$(_COLOR)make$(_END)] clean done\n"

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)/$(NAME)
	@printf "[$(_COLOR)make$(_END)] fclean done\n"

re: fclean
re:	all

.PHONY: all fclean clean library re release tests