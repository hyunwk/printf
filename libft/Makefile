# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:05:10 by hyunwkim          #+#    #+#              #
#    Updated: 2021/07/03 16:53:51 by hyunwkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar 
ARFLAGS = rcs
RM = rm -f

FUNC =	ft_memset\
		ft_bzero \
		ft_memcpy \
		ft_strlen \
		ft_strchr \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlcpy \
		ft_strlcat \
		ft_strrchr \
		ft_strnstr \
		ft_strmapi \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_putendl_fd

FUNC_BONUS = ft_lstnew\
	ft_lstadd_front\
	ft_lstsize\
	ft_lstlast\
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap \

SRCS = $(addsuffix .c, $(FUNC))
SRCS_BONUS = $(addsuffix .c, $(FUNC_BONUS))

OBJS = $(addsuffix .o, $(FUNC))
OBJS_BONUS = $(addsuffix .o, $(FUNC_BONUS))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

bonus: $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re
