# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 21:30:15 by hyunwkim          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/07/08 18:47:44 by hyunwkim         ###   ########.fr        #
=======
#    Updated: 2021/07/19 18:20:39 by hyunwkim         ###   ########.fr        #
>>>>>>> flag
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a
<<<<<<< HEAD

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

=======
>>>>>>> flag
INCS		= .
RM			= rm -f
LIBC		= ar rcs

SRCS		= ./ft_printf.c ./util.c
OBJS		= $(SRCS:.c=.o)

<<<<<<< HEAD
.c.o :
	$(CC) $(CFLAGS) -c -o $@ $< 
=======
FUNC        = ft_printf print_str print_num print_hex num_utils hex_utils print_utils

SR 		= $(addsuffix .c, $(FUNC))
SRCS        = $(addprefix srcs/, $(SR))
SR_BONUS  = $(addsuffix _bonus.c, $(FUNC))
SRCS_BONUS  = $(addprefix bonus/, $(SR_BONUS))

OB 		= $(addsuffix .o, $(FUNC))
OBJS        = $(addprefix srcs/, $(OB))
OB_BONUS  = $(addsuffix _bonus.o, $(FUNC))
OBJS_BONUS  = $(addprefix bonus/, $(OB_BONUS))

.c.o : $(SRCS) $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c -o $@ $^
>>>>>>> flag

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)

all : $(NAME)

<<<<<<< HEAD
=======
bonus : $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^

>>>>>>> flag
clean :
	$(RM) $(OBJS) $(OBJS_BONUS) $(LIBFT_LIB)
	make clean -C $(LIBFT)

fclean : clean
	$(RM) $(NAME)
<<<<<<< HEAD
	make fclean -C $(LIBFT)
=======
>>>>>>> flag

re : fclean all

.PHONY: all clean clean re
