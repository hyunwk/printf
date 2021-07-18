/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/18 20:39:56 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(char c, t_info *info)
{
	if (c == '-')
		info->left_align = 1;
	if (c == '.')
		info->dot = 1;
	if (c == '0' && info->dot == 0)
		info->zero = 1;
}

int	get_format_info(const char *line, t_info *info)
{
	int	idx;

	idx = 0;
	while (ft_strchr(FLAG, line[idx]))
		get_flags(line[idx++], info);
	if ('1' <= line[idx] && line[idx] <= '9')
		idx += is_num(&line[idx], info);
	while (ft_strchr(FLAG, line[idx]))
	{
		if (info->dot == 1 && line[idx] == '0')
			break ;
		get_flags(line[idx++], info);
	}
	if ('0' <= line[idx] && line[idx] <= '9')
		idx += is_num(line + idx, info);
	if (ft_strchr(TYPE, line[idx]) || line[idx] == '%')
		info->type = line[idx++];
	return (idx + 1);
}

int	check_format(const char *line, t_info *info, va_list *ap)
{
	int	rtn;

	init_info(info);
	rtn = get_format_info(line, info);
	if (info->type == '%')
		print_char('%', info);
	else if (info->type == 'c')
		print_char(va_arg(*ap, int), info);
	else if (info->type == 's')
		print_str(va_arg(*ap, char *), info);
	else if (info->type == 'd' || info->type == 'i')
		print_num(va_arg(*ap, int), info);
	else if (info->type == 'u')
		print_num(va_arg(*ap, unsigned int), info);
	else if (info->type == 'x' || info->type == 'X')
		parse_hex(va_arg(*ap, unsigned int), info);
	else if (info->type == 'p')
		parse_hex(va_arg(*ap, unsigned long long), info);
	return (rtn);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_info	*info;
	int		written_len;
	int		rtn;

	va_start(ap, format);
	info = malloc(sizeof(t_info) * 1);
	if (!info)
		return (-1);
	info->size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			written_len = check_format(format + 1, info, &ap);
			format += written_len;
		}
		else
			ft_putchar(*(format++), info);
	}
	va_end(ap);
	rtn = info->size;
	free(info);
	return (rtn);
}

void	init_info(t_info *info)
{
	info->zero = 0;
	info->width = 0;
	info->left_align = 0;
	info->dot = 0;
	info->prec = 0;
}
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
	}
	else if (info->prec >= info->width && info->width > get_num_len(*n))
		print_multi_str(info->prec - get_num_len(*n), info);
	else
		return (0);
	return (1);
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
		if (!(*n) && info->dot != 0)
			print_multi_str(info->width - get_num_len(*n) + 1, info);
		else
			print_multi_str(info->width - get_num_len(*n), info);
	}
	return (1);
}

//#include<stdio.h>
//int main()
//{
//	ft_printf("%-4d",-2464);
//	printf("%-4d",-2464);
//}
