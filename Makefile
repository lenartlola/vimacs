# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 13:18:57 by hsabir            #+#    #+#              #
#    Updated: 2022/01/08 16:15:08 by hsabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ftvim

LFT_DIR = libs/libft
LFT_NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Dynamically link the ncurses lib
#CFLAGS += -lncurses # To run it in another computer,
                    # ncurses library should be installed.
		    # In most of unix system ncurses is installed
		    # by default. it can be found in /usr/lib or /usr/include
# Debug mode
CFLAGS += -g3 -fsanitize=address

DBG_SRCS = ftvim.dSYM

FILES = ./srcs/main.c

all : $(NAME)

$(NAME): $(LFT_NAME)
	$(CC) $(CFLAGS) $(FILES) $(LFT_NAME) -o $(NAME)

$(LFT_NAME):
	$(MAKE) all -sC $(LFT_DIR)/
	cp $(LFT_DIR)/$(LFT_NAME) $(LFT_NAME)

fclean:
	rm -f $(NAME)
	rm -f $(LFT_NAME)
	rm -rf $(DBG_SRCS)
	$(MAKE) fclean -sC $(LFT_DIR)/

clean:
	rm -f $(LFT_NAME)
	$(MAKE) fclean -sC $(LFT_DIR)/

re: fclean all
	$(MAKE) re -sC $(LFT_DIR)

.PHONY: clean fclean all re
