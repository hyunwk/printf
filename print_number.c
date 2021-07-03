/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:13:01 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/03 21:21:52 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_num(const char *s, t_info *info)
{
	int	idx;
	int	num;

	idx = 0;
	num = 0;
	while ('0' <= s[idx] && s[idx] <= '9')
	{
		num = num * 10 + s[idx] - '0';
		idx++;
	}
	if (!info->width && info->dot == -1)
		info->width = num;
	else if (info->dot != -1)
		info->prec = num;
	return (idx);
}

//int	get_int_digits(int n)
//{
//	int	i;
//
//  if (!n)
//  return (1);
//
//	i = 0;
//	if (n < 0)
//	{
//		n *= -1;
//		i++;
//	}
//	while (n)
//	{
//		n /= 10;
//		i++;
//	}
//	return (i);
//}

int	is_minus(int n)
{
	return (n < 0);
}

//int	print_num(int n, t_info *info)
//{
//	if (info->left_align)
//	{
//		ft_putnbr(n, info);
//		if (info->width > get_int_digits(n))
//			print_multi_str(info->width - get_int_digits(n), info);
//	}
//	else
//	{
//		if (info->prec > get_int_digits(n))
//		{
//			print_multi_str(info->width - info->prec - is_minus(n), info);
//			info->zero = 1;
//		}
//		else if (info->width > get_int_digits(n))
//			print_multi_str(info->width - get_int_digits(n), info);
//		if (is_minus(n))
//		{
//			ft_putchar('-', info);
//			n *= -1;
//		}
//		if (info->prec > get_int_digits(n))
//			print_multi_str(info->prec - get_int_digits(n), info);
//		ft_putnbr(n, info);
//	}
//	return (1);
//}
