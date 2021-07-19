/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:17:59 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 16:18:04 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

void	ft_putnbr(long long n, t_info *info)
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
}

void	print_multi_str(int time, t_info *info)
{
	int		idx;
	char	c;

	idx = 0;
	if (info->zero)
		c = '0';
	else
		c = ' ';
	while (idx++ < time)
		ft_putchar(c, info);
}
