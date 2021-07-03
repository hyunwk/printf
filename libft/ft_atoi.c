/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:15:47 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 15:09:07 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	to_long(const char *str, int sign)
{
	long long		num;
	int				i;

	num = 0;
	i = 0;
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		i++;
		if (i == 20)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (num * sign);
}

int					ft_atoi(const char *str)
{
	int				sign;

	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str == '-' || *str == '+')
		return (0);
	return (to_long(str, sign));
}
