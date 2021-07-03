/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:36:03 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 15:30:32 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		*alloc(int word_len, int sign, unsigned int num)
{
	int				idx;
	char			*p;

	idx = word_len + sign - 1;
	if (!(p = (char *)malloc(sizeof(char) * (word_len + sign + 1))))
		return (NULL);
	if (sign)
		p[0] = '-';
	while (idx >= sign)
	{
		p[idx--] = num % 10 + '0';
		num = num / 10;
	}
	p[word_len + sign] = 0;
	return (p);
}

char				*ft_itoa(int n)
{
	int				sign;
	int				word_len;
	unsigned int	num;

	sign = 0;
	word_len = 0;
	num = n;
	if (n == 0)
		word_len = 1;
	if (n < 0)
	{
		sign = 1;
		num = n * -1;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		word_len++;
	}
	return (alloc(word_len, sign, num));
}
