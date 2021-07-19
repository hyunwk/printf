# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 21:30:15 by hyunwkim          #+#    #+#              #
#    Updated: 2021/07/19 18:20:39 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a
INCS		= .
RM			= rm -f
LIBC		= ar rc
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

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

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)

all : $(NAME)

bonus : $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^

clean :
	$(RM) $(OBJS) $(OBJS_BONUS) $(LIBFT_LIB)
	make clean -C $(LIBFT)

fclean : clean
	$(RM) $(NAME)

re : fclean all
