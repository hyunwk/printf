/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:25:41 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/14 19:21:13 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_info *info)
{
	write(1, &c, 1);
	info->size += 1;
}

void	ft_putstr(char *s, int time, t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < time)
	{
		ft_putchar(*s, info);
		s++;
		idx++;
	}
}

void	init_info(t_info *info)
{
	info->zero = 0;
	info->width = 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	//info->prec = -1;
	info->prec = 0;
}
