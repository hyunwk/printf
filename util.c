/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:47:04 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/08 18:05:53 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

int	get_hex_digits(unsigned long long n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_putchar(char c, int *rtn)
{
	write(1, &c, 1);
	(*(rtn))++;
}

int	ft_putnbr(long long n, char type, int *rtn)
{
	long long	temp;

	temp = n;
	if (type == 'd' && (temp < -2147483648 || temp > 2147483648))
		return (0);
	else if (type == 'u' && (temp < 0 || temp > 4294967295))
		return (0);
	if (temp < 0)
	{
		ft_putchar('-', rtn);
		temp = -temp;
	}
	if (temp >= 10)
	{
		ft_putnbr(temp / 10, type, rtn);
		ft_putchar(temp % 10 + '0', rtn);
	}
	if (temp < 10)
		ft_putchar(temp % 10 + '0', rtn);
	return (1);
}

void	ft_putstr(char *s, int *rtn)
{
	int	idx;

	idx = 0;
	while (idx < (int)ft_strlen(s))
	{
		ft_putchar(s[idx], rtn);
		idx++;
	}
}
