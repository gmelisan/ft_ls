#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/01 16:04:42 by gmelisan          #+#    #+#              #
#    Updated: 2019/02/11 10:45:30 by gmelisan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls
LIBDIR = ./libft
LIBINC = ./libft/includes
LIB = libft.a

CC = clang
CFLAGS = -Wall -Wextra -g
#CFLAGS += -Werror

OBJ = $(sort \
main.o parse_args.o show_error.o sort_names.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBDIR)/$(LIB) $(OBJ)
	$(CC) $(CFLAGS) -I. -o $@ $(OBJ) -L$(LIBDIR) -lft
	@echo "\033[0;32mFile $@ was successfully created.\033[0m"

$(OBJ): $(NAME).h

$(LIBDIR)/$(LIB):
	@make -C $(LIBDIR)

lib:
	@make -C $(LIBDIR)

%.o : %.c
	@$(CC) $(CFLAGS) -I. -I$(LIBINC) -c -o $@ $< 
	@echo "\033[1;34mCompiling ($(CFLAGS)) \033[0;36m$<\033[0m"

clean:
	@make -C $(LIBDIR) clean
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIBDIR)/$(LIB)
	@rm -f $(NAME)

re: fclean all
