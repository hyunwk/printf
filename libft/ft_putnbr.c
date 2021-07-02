/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:49:40 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 19:06:50 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_putnbr(int n, t_info *info)
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
