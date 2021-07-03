/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:14:00 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/03 17:31:13 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
///////////////
///////////////print_str function has deleted, need to add before submit
///////////////
///////////////
///////////////
///////////////
///////////////
///////////////
///////////////
///////////////
///////////////
///////////////
void	print_multi_str(int time, t_info *info)
{
	int		idx;
	char	c;

	idx = 0;
	if (info->zero && !info->left_align)
		c = '0';
	else
		c = ' ';
	while (idx++ < time)
		ft_putchar(c, info);
}

int	print_char(char c, t_info *info)
{
	if (info->left_align)
	{
		ft_putchar(c, info);
		if (info->width)
			print_multi_str(info->width - 1, info);
	}
	else
	{
		if (info->width)
			print_multi_str(info->width - 1, info);
		ft_putchar(c, info);
	}
	return (1);
}

char	*get_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

int	print_hex(unsigned long long n, t_info *info)
{
	char	*hex_arr;
	int		i;

	i = 8;
	hex_arr = (char *)malloc(sizeof(char) * 9);
	if (!hex_arr)
		return (ERR);
	if (info->type == 'p' || info->type == 'x')
		ft_putstr("0x", 2, info);
	else if (info->type == 'X')
		ft_putstr("0X", 2, info);
	while (n)
	{
		hex_arr[i--] = get_base(info->type)[n % 16];
		n /= 16;
	}
	print_str(hex_arr, info);
	free(hex_arr);
	return (1);
}
