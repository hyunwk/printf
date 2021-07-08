# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 21:30:15 by hyunwkim          #+#    #+#              #
#    Updated: 2021/07/08 18:47:44 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

INCS		= .
RM			= rm -f
LIBC		= ar rcs

SRCS		= ./ft_printf.c ./util.c
OBJS		= $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -c -o $@ $< 

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(RM) $(OBJS)
	make clean -C $(LIBFT)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)

re : fclean all

.PHONY: all clean clean re
