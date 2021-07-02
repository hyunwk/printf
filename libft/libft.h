/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:05:45 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 15:10:52 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
#include "../ft_printf.h"

typedef struct st_info
{
	char	type;
	int		size; // printf return len
	int		zero; // flag zero
	int		width; // flag width size
	int		precise; // flag precise
	int		left_align;
	int		asterisk; // flag *
	int		dot;      // flag .
} s_info;

int			ft_strlen(char *s);
void		ft_putchar(char c, s_info *info);
char		*ft_strchr(const char *s, int c);
void		ft_putstr(char *s, int time, s_info *info);

#endif
