/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:17:52 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 16:17:54 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_char(char c, t_info *info)
{
	if (info->left_align)
	{
		ft_putchar(c, info);
		if (info->width)
		{
			info->zero = 0;
			print_multi_str(info->width - 1, info);
		}
	}
	else
	{
		if (info->width)
			print_multi_str(info->width - 1, info);
		ft_putchar(c, info);
	}
	return (1);
}

int	print_str(char *s, t_info *info)
{
	int	is_null;

	is_null = 0;
	if (!s)
	{
		s = ft_strdup("(null)");
		is_null = 1;
	}
	if ((int)ft_strlen(s) >= info->width && info->width > 0)
		print_str_bigger_len(s, info);
	else
	{
		if (info->width > (int)ft_strlen(s))
			print_str_bigger_width(s, info);
		else
		{
			if ((int)ft_strlen(s) > info->prec && info->dot == 1)
				ft_putstr(s, info->prec, info);
			else
				ft_putstr(s, ft_strlen(s), info);
		}
	}
	if (is_null)
		free(s);
	return (1);
}

void	print_str_bigger_len(char *s, t_info *info)
{
	if (info->width > info->prec && info->dot == 1 && !info->left_align)
		print_multi_str(info->width - info->prec, info);
	if (info->prec <= (int)ft_strlen(s) && info->dot == 1)
		ft_putstr(s, info->prec, info);
	else
		ft_putstr(s, ft_strlen(s), info);
	if (info->width > info->prec && info->dot == 1 && info->left_align)
		print_multi_str(info->width - info->prec, info);
}

void	print_str_bigger_width(char *s, t_info *info)
{
	if (info->prec < (int)ft_strlen(s) && info->dot == 1)
	{
		if (!info->left_align)
			print_multi_str(info->width - info->prec, info);
		ft_putstr(s, info->prec, info);
		if (info->left_align)
			print_multi_str(info->width - info->prec, info);
	}
	else
	{
		if (!info->left_align)
			print_multi_str(info->width - (int)ft_strlen(s), info);
		ft_putstr(s, ft_strlen(s), info);
		if (info->left_align)
			print_multi_str(info->width - (int)ft_strlen(s), info);
	}
}
