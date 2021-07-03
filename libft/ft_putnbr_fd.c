/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:08:47 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 15:40:01 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		write_int(int nb, int fd)
{
	int			i;
	char		s[20];

	i = 0;
	while (nb != 0)
	{
		s[i++] = nb % 10 + '0';
		nb /= 10;
	}
	while (i > 0)
		write(fd, &s[--i], 1);
}

static void		ft_putnbr(int nb, int fd)
{
	if (nb == 0)
		write(fd, "0", 1);
	else if (nb > 0)
		write_int(nb, fd);
	else if (nb == -2147483648)
	{
		nb /= 10;
		nb *= -1;
		write(fd, "-", 1);
		write_int(nb, fd);
		write(fd, "8", 1);
	}
	else if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
		write_int(nb, fd);
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}
