# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 21:30:15 by hyunwkim          #+#    #+#              #
#    Updated: 2021/07/19 16:36:06 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
LIBFT		= libft
LIBFT_LIB	= libft.a

FUNC        = ft_printf print_str print_num print_hex num_utils hex_utils print_utils

SR 		= $(addsuffix .c, $(FUNC))
SRCS        = $(addprefix srcs/, $(SR))
SR_BONUS  = $(addsuffix _bonus.c, $(FUNC))
SRCS_BONUS  = $(addprefix bonus/, $(SR_BONUS))

OB 		= $(addsuffix .o, $(FUNC))
OBJS        = $(addprefix srcs/, $(OB))
OB_BONUS  = $(addsuffix _bonus.o, $(FUNC))
OBJS_BONUS  = $(addprefix bonus/, $(OB_BONUS))

#OBJS		= $(SRCS:.c=.o)
INCS		= .
RM			= rm -f
LIBC		= ar rc
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

#.c.o :
	#$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INCS)
.c.o : $(SRCS) $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c -o $@ $^

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)

all : $(NAME)

bonus : $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)

clean :
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIBFT)

re : fclean all
