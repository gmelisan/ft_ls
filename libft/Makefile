# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kemmeric <kemmeric@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 12:48:23 by gmelisan          #+#    #+#              #
#    Updated: 2019/01/31 23:55:05 by gmelisan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INCDIR = ./includes
FTPRINTF_DIR = ./ft_printf

CC = clang
CFLAGS = -Wall -Wextra -Werror

OBJ = $(sort \
ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o \
ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o \
ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o \
ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o \
ft_isprint.o ft_toupper.o ft_tolower.o ft_isspace.o ft_memalloc.o \
ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o \
ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o \
ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o \
ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o \
ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o \
ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o \
ft_abs.o ft_swap.o ft_range.o ft_power.o ft_realloc.o get_next_line.o \
ft_lstaddback.o ft_strarrdel.o get_lines.o ft_lstsize.o \
ft_atoi.o ft_itoa.o )

OBJ_FTPRINTF = $(sort $(addprefix $(FTPRINTF_DIR)/, \
ft_printf.o ft_vprintf.o ft_fdprintf.o ft_vfdprintf.o \
get_conversion.o get_flags.o get_width.o get_precision.o get_length.o \
handle_conversion.o \
handle_unknown.o \
handle_char.o handle_string.o \
handle_wchar.o handle_wstring.o \
handle_integer.o convert_integer.o number_to_string.o \
handle_float.o convert_float.o \
number_to_string_f.o number_to_string_e.o \
get_color.o handle_color.o ))

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_FTPRINTF)
	@ar rc $@ $^
	@ranlib $@
	@echo "\033[0;32mFile $@ was successfully created.\033[0m"

$(OBJ): $(INCDIR)/libft.h

$(OBJ_FTPRINTF): $(INCDIR)/ft_printf.h $(INCDIR)/libft.h

%.o : %.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<
	@echo "\033[1;34mCompiling ($(CFLAGS)) \033[0;36m$<\033[0m"

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_FTPRINTF)

fclean: clean
	@rm -f $(NAME)

re: fclean all
