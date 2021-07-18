/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 20:02:31 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/17 19:58:23 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_num_len(long long n)
{
	long long	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	is_minus(int n)
{
	return (n < 0);
}

int	is_num(const char *s, t_info *info)
{
	int	idx;
	int	num;

	idx = 0;
	num = 0;
	while ('0' <= s[idx] && s[idx] <= '9')
	{
		num = num * 10 + s[idx] - '0';
		idx++;
	}
	if (!info->width && info->dot == 0)
		info->width = num;
	else if (info->dot != 0)
		info->prec = num;
	return (idx);
}
