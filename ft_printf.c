/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/08 15:54:37 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(char c, t_info *info)
{
	if (c == '-')
		info->left_align = 1;
	if (c == '.')
		info->dot = 1;
	if (c == '0')
		info->zero = 1;
}

void	get_asterisk(t_info *info, va_list ap)
{
	int	num;

	info->asterisk = 1;
	num = va_arg(ap, int);
	if (num < 0)
	{
		if (info->dot == -1)
		{
			info->width = num * -1;
			info->left_align = 1;
		}
		else
		{
			info->asterisk = -1;
			info->dot = -1;
		}
	}
	else if (!info->width)
	{
		if (info->dot == -1)
			info->width = num;
		else
			info->prec = num;
	}
}

int	get_format_info(const char *line, t_info *info, va_list ap)
{
	int	idx;

	idx = 0;
	while (ft_strchr(FLAG, line[idx]))
		get_flags(line[idx++], info);
	if ('1' <= line[idx] && line[idx] <= '9')
		idx += is_num(&line[idx], info);
	while (ft_strchr(FLAG, line[idx]))
	{
		get_flags(line[idx], info);
		if ('*' == line[idx++])
			get_asterisk(info, ap);
	}
	if ('1' <= line[idx] && line[idx] <= '9' && !info->asterisk)
		idx += is_num(line + idx, info);
	if (ft_strchr(TYPE, line[idx]) || line[idx] == '%')
		info->type = line[idx++];
	else
		return (ERR);
	return (idx);
}

int	check_format(const char *line, t_info *info, va_list ap)
{
	int	rtn;

	init_info(info);
	//rtn = get_format_info(line, info, ap);
	rtn = get_format_info(line, info, ap);
	if (info->type == '%')
	{
		ft_putchar('%', info);
		return (rtn + 1);
	}
	else if (info->type == 'c')
	{
		ft_putchar(va_arg(ap, int), info);
		return (rtn + 1);
	}
	else if (info->type == 's')
		return (print_str(va_arg(ap, char *), info) + rtn);
	else if (info->type == 'p' )
		return (print_hex(va_arg(ap, unsigned long long), info) + rtn);
	else if (info->type == 'x' || info->type == 'X')
		return (print_hex(va_arg(ap, unsigned int), info) + rtn);
	else if (info->type == 'd' || info->type == 'i')
		return (ft_putnbr(va_arg(ap, int), info) + rtn);
	else if (info->type == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int), info) + rtn);
	return (rtn);
}
int	print_hex(unsigned long long n, t_info *info)
{
	char	*hex_arr;
	int		idx;

	idx = get_hex_digits(n);
	hex_arr = (char *)malloc(sizeof(char) * (idx + 1));
	if (!hex_arr)
		return (ERR);
	if (info->type == 'p')
		ft_putstr("0x", 2, info);
	if (n)
	{
		while (n)
		{
			hex_arr[--idx] = get_base(info->type)[n % 16];
			n /= 16;
		}
		print_str(hex_arr, info);
	}
	else
		ft_putchar('0', info);
	free(hex_arr);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_info	*info;
	int		written_len;

	va_start(ap, format);
	info = malloc(sizeof(t_info) * 1);
	if (!info)
		return (-1);
	info->size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			written_len = check_format(format + 1, info, ap);
			format += written_len;
		}
		else
		{
			ft_putchar(*format, info);
			format++;
		}
	}
	va_end(ap);
	return (info->size);
}
void	ft_putchar(char c, t_info *info)
{
	write(1, &c, 1);
	info->size += 1;
}
int	print_str(char *s, t_info *info)
{
	if (!s)
		s = ft_strdup("(null)");
	ft_putstr(s, ft_strlen(s), info);
	if (!ft_strncmp(s,"(null)", 6))
		free(s);
	return (1);
}

int	get_hex_digits(int n)
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

int	ft_putnbr(long long n, t_info *info)
{
	long long temp;

	temp = n;
	if (temp < -2147483648 || temp > 2147483648)
		return (0);
	if (temp < 0)
	{
		ft_putchar('-', info);
		temp = -temp;
	}
	if (temp >= 10)
	{
		ft_putnbr(temp / 10, info);
		ft_putchar(temp % 10 + '0', info);
	}
	if (temp < 10)
		ft_putchar(temp % 10 + '0', info);
	return (1);
}

#include<stdio.h>
int main()
{
	printf("%d\n", -2147483647);
	printf("%d\n", 2147483647);
}
