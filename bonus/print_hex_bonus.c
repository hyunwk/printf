/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:57:09 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 16:51:39 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_hex(char *s, t_info *info)
{
	if (info->left_align)
	{
		if (print_hex_left(s, info))
			;
		else
			print_hex_left_else(s, info);
	}
	else
	{
		print_hex_right(s, info);
		if (info->prec > 0 || info->dot != 1 \
				|| (info->type != 'p' && s[0] != '0'))
			ft_putstr(s, (int)ft_strlen(s), info);
		else if (info->type == 'p')
			ft_putstr("0x", 2, info);
	}
	return (1);
}

int	print_hex_left(char *s, t_info *info)
{
	if (info->width >= info->prec && info->prec >= (int)ft_strlen(s))
	{
		info->zero = 1;
		print_multi_str(info->prec - (int)ft_strlen(s), info);
		ft_putstr(s, (int)ft_strlen(s), info);
		info->zero = 0;
		print_multi_str(info->width - info->prec, info);
	}
	else if (info->width >= (int)ft_strlen(s) && (int)ft_strlen(s) > info->prec)
	{
		if (s[0] == '0' && info->dot == 1)
			print_multi_str(info->width, info);
		else
		{
			ft_putstr(s, (int)ft_strlen(s), info);
			print_multi_str(info->width - (int)ft_strlen(s), info);
		}
	}
	else
		return (0);
	return (1);
}

void	print_hex_left_else(char *s, t_info *info)
{
	if (info->prec >= info->width)
	{
		info->zero = 1;
		print_multi_str(info->prec - (int)ft_strlen(s), info);
	}
	ft_putstr(s, (int)ft_strlen(s), info);
}

void	print_hex_right(char *s, t_info *info)
{
	if (info->prec > (int)ft_strlen(s))
	{
		if (info->width > info->prec)
		{
			info->zero = 0;
			print_multi_str(info->width - info->prec, info);
		}
		info->zero = 1;
		print_multi_str(info->prec - (int)ft_strlen(s), info);
	}
	else if (info->prec >= info->width && info->width > (int)ft_strlen(s))
		print_multi_str(info->prec - (int)ft_strlen(s), info);
	else if (info->width > (int)ft_strlen(s) && (int)ft_strlen(s) > info->prec)
	{
		if (info->dot == 0 && info->zero)
			info->zero = 1;
		else
			info->zero = 0;
		if (s[0] == '0' && info->dot == 1 && info->type == 'p')
			print_multi_str(info->width - 2, info);
		else if (s[0] == '0' && info->dot == 1)
			print_multi_str(info->width, info);
		else
			print_multi_str(info->width - (int)ft_strlen(s), info);
	}
}
