/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 20:01:35 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 14:23:24 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_hex(unsigned long long n, t_info *info)
{
	char	*hex_arr;
	int		hex_len;

	hex_len = get_hex_len(n);
	if (info->type == 'p')
		hex_len += 2;
	hex_arr = (char *)malloc(sizeof(char) * (hex_len + 1));
	if (!hex_arr)
		return (ERR);
	hex_arr[hex_len] = 0;
	if (info->type == 'p')
		ft_strlcpy(hex_arr, "0x0", 4);
	if (n)
	{
		while (n)
		{
			hex_arr[--hex_len] = get_base(info->type)[n % 16];
			n /= 16;
		}
	}
	else if (info->type != 'p' || n)
		hex_arr[0] = '0';
	print_hex(hex_arr, info);
	free(hex_arr);
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

int	get_hex_len(unsigned long long n)
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
