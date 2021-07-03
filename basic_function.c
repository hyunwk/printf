/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:25:41 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/03 20:55:39 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_info *info)
{
	write(1, &c, 1);
	info->size += 1;
}

int	ft_putnbr(int n, t_info *info)
{
	if (n < 0)
	{
		ft_putchar('-', info);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, info);
		ft_putchar(n % 10 + '0', info);
	}
	if (n < 10)
		ft_putchar(n % 10 + '0', info);
	return (n);
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
	info->prec = 0;
}
