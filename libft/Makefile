# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:05:10 by hyunwkim          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/07/08 18:39:32 by hyunwkim         ###   ########.fr        #
=======
#    Updated: 2021/07/19 15:00:27 by hyunwkim         ###   ########.fr        #
>>>>>>> flag
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f
LIBC = ar rcs

<<<<<<< HEAD
SRCS =	./ft_strlen.c ./ft_strchr.c ./ft_strncmp.c ./ft_strdup.c
=======
SRCS =	./ft_strlen.c ./ft_strchr.c ./ft_strncmp.c ./ft_strdup.c ./ft_strlcpy.c
>>>>>>> flag
OBJS = $(SRCS:.c=.o)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(LIBC) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
