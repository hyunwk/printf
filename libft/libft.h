/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:05:45 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 16:45:13 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "../ft_printf.h"

typedef struct s_info
{
	char	type;
	int		size;
	int		zero;
	int		width;
	int		prec;
	int		left_align;
	int		asterisk;
	int		dot;
}	t_info;

int			ft_strlen(char *s);
void		ft_putchar(char c, t_info *info);
char		*ft_strchr(const char *s, int c);
void		ft_putstr(char *s, int time, t_info *info);

#endif
