/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:13:01 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/18 23:08:09 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_num(long long n, t_info *info)
{
	if (info->left_align)
	{
		if (print_num_left_bigger_width(&n, info))
			;
		else
			print_num_left_else(&n, info);
	}
	else
	{
		if (print_num_right_bigger_prec(&n, info))
			;
		else
			print_num_right_else(&n, info);
		if (n || info->prec > 0 || info->dot != 1)
			ft_putnbr(n, info);
	}
	return (1);
}

int	print_num_left_bigger_width(long long *n, t_info *info)
{
	if (info->width >= info->prec && info->prec >= get_num_len(*n))
	{
		if (is_minus(*n))
		{
			ft_putchar('-', info);
			*n *= -1;
			info->width -= 1;
		}
		info->zero = 1;
		print_multi_str(info->prec - get_num_len(*n), info);
		ft_putnbr(*n, info);
		info->zero = 0;
		print_multi_str(info->width - info->prec, info);
	}
	else if (info->width >= get_num_len(*n) && get_num_len(*n) > info->prec)
	{
		if (*n || info->dot == 0)
			ft_putnbr(*n, info);
		else
			info->width += 1;
		print_multi_str(info->width - get_num_len(*n), info);
	}
	else
		return (0);
	return (1);
}

int	print_num_left_else(long long *n, t_info *info)
{
	if (info->prec >= info->width || info->prec >= get_num_len(*n))
	{
		if (is_minus(*n))
		{
			ft_putchar('-', info);
			*n *= -1;
		}
		if (get_num_len(*n) > info->width || info->prec > get_num_len(*n))
			info->zero = 1;
		print_multi_str(info->prec - get_num_len(*n), info);
		if (*n)
			ft_putnbr(*n, info);
	}
	else if (!info->prec || !info->dot)
		ft_putnbr(*n, info);
	return (1);
}

int	print_num_right_bigger_prec(long long *n, t_info *info)
{
	if (info->prec >= get_num_len(*n))
	{
		if (info->width > info->prec)
		{
			info->zero = 0;
			print_multi_str(info->width - info->prec - is_minus(*n), info);
		}
		if (is_minus(*n))
		{
			ft_putchar('-', info);
			*n *= -1;
		}
		info->zero = 1;
		print_multi_str(info->prec - get_num_len(*n), info);
		return (1);
	}
	return (0);
}

int	print_num_right_else(long long *n, t_info *info)
{
	if (info->width >= get_num_len(*n) && get_num_len(*n) > info->prec)
	{
		if (is_minus(*n) && info->zero && info->dot == 0)
		{
			ft_putchar('-', info);
			*n *= -1;
			info->width -= 1;
		}
		if (info->dot == 0 && info->zero)
			info->zero = 1;
		else
			info->zero = 0;
		if (*n || info->dot == 0)
			print_multi_str(info->width - get_num_len(*n), info);
		else
			print_multi_str(info->width - get_num_len(*n) + 1, info);
	}
	return (1);
}
