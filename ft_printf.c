/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 20:47:58 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include<stdio.h>

int	ft_strlen(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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

void	ft_putchar(char c, t_info *info)
{
	write(1, &c, 1);
	info->size += 1;
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!(*s))
			return (0);
		s++;
	}
	return ((char *)s);
}

void	ft_putstr(char *s, int time, t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < time)
	{
		ft_putchar(*s, info);
		s++;
		idx++;
	}
}

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

void	init_info(t_info *info)
{
	info->zero = 0;
	info->width= 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	info->prec = -1; // dot and prec duplicated
}

void	print_multi_str(int time, t_info *info)
{
	int	idx;
	char	c;

	idx = 0;
	if (info->zero && !info->left_align)
		c = '0';
	else
		c = ' ';
	while (idx++ < time)
		ft_putchar(c, info);
}

int	print_str(char *s, t_info *info)
{
	int	space_len;

	space_len = ft_strlen(s) - info->width ;
	if (!s)
		return (ERR);
	if (space_len >= 0 && info->dot != -1 && ft_strlen(s) > info->prec)
	{
		if (info->width > info->prec)
			print_multi_str(info->width - info->prec, info);
		ft_putstr(s, info->prec, info);
	}
	else if (space_len >= 0 && (ft_strlen(s) <= info->prec || info->prec == -1))
		ft_putstr(s, ft_strlen(s), info);
	else if (info->left_align)
	{
		ft_putstr(s, ft_strlen(s), info);
		print_multi_str(info->width - ft_strlen(s), info); 
	}
	else
	{
		print_multi_str(info->width - ft_strlen(s), info);
		ft_putstr(s, ft_strlen(s), info);
	}
	return (1);
}

int		print_char(char c, t_info *info)
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
		{
//			if (info->zero)
//				print_multi_str(info->width - 1, info);
//			else
//				print_multi_str(info->width - 1, info);
			print_multi_str(info->width - 1, info);
		}
		ft_putchar(c, info);
	}
	return (1);
}

int		get_int_digits(int n)
{
	int i;

	i = 0;
	if (n < 0)
	{	
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		is_minus(int n)
{
	return (n < 0);
}

int		print_num(int n, t_info *info)
{
	if (info->left_align)
	{
		ft_putnbr(n, info);
		if (info->width > get_int_digits(n))
			print_multi_str(info->width - get_int_digits(n), info);
	}
	else
	{
		if (info->prec > get_int_digits(n))
		{
			print_multi_str(info->width - info->prec - is_minus(n), info);
			info->zero = 1;
		}
		else if (info->width > get_int_digits(n))
			print_multi_str(info->width - get_int_digits(n), info);
		if (is_minus(n))
		{
			ft_putchar('-', info);
			n *= -1;
		}
		if (info->prec > get_int_digits(n))
			print_multi_str(info->prec - get_int_digits(n), info);
		ft_putnbr(n, info);
	}
	return (1);
}

void	get_flags(char c, t_info *info)
{
	if (c == '-')
		info->left_align = 1;
	if (c  == '.')
		info->dot = 1;
	if (c == '0')
		info->zero = 1;
}

void	get_asterisk(t_info *info, va_list *ap)
{
	int num;

	info->asterisk = 1;
	num = va_arg(*ap, int);
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

int get_format_info(const char *line, t_info *info, va_list *ap)
{
	int	idx;

	idx = 0;
	//width || 0처리
	if (line[idx] && '1' <= line[idx] && line[idx] <= '9')
		idx += is_num(&line[idx], info);

	// flag
	while (ft_strchr(FLAG, line[idx]))
	{
		get_flags(line[idx], info);
		if ('*' == line[idx])
			get_asterisk(info, ap);
		idx++;
	}

	// check prec
	if (is_num(line + idx, info) && !info->asterisk)
		idx += is_num(line + idx, info);

	// check flag_type ,   what if err?
	if (ft_strchr(TYPE, line[idx]))
		info->type = line[idx++];
	else
		return (ERR);
	return (idx);
}

char *get_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

int print_hex(unsigned long long n, t_info *info)
{
	char	*hex_arr;
	int		i;

	i = 0;
	hex_arr = (char *)malloc(sizeof(char) * 9);
	if (info->type == 'p' || info->type == 'x')
		ft_putstr("0x", 2, info);
	else if (info->type == 'X')
		ft_putstr("0X", 2, info);
	while (n)
	{
		hex_arr[i++] = get_base(info->type)[n % 16];
		n /= 16;
	}
	while (i > 0)
		ft_putchar(hex_arr[--i], info);
	return (1);
}

int	check_format(const char *line, t_info *info, va_list *ap)
{
	int rtn;

	init_info(info);
	rtn = get_format_info(line, info, ap);
	if (*line == '%')
		//print_char('%', info);
		ft_putchar('%', info);
	else if (info->type == 'c')
		return (print_char(va_arg(*ap, int), info) + rtn);
	else if (info->type == 's')
		return (print_str(va_arg(*ap, char *), info) + rtn);
	else if (info->type == 'p')
		return (print_hex(va_arg(*ap, unsigned long long), info) + rtn);
	else if (info->type == 'd')
		return (print_num(va_arg(*ap, int), info) + rtn);
	else if (info->type == 'i')
		return (print_num(va_arg(*ap, int), info) + rtn);
	else if (info->type == 'u')
		return (print_num((unsigned int)va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'x')
//		return (print_hex((unsigned int)va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'X')
//		return (print_hex((unsigned int)va_arg(*ap, int), info) + rtn);
	return (rtn);
}

int ft_printf(const char *line, ...)
{
	va_list ap;
	t_info	*info;
	int		written_len;

	va_start(ap, line);

	if (!(info = malloc(sizeof(t_info) * 1)))
		return (-1);
	info->size = 0;

	while (*line)
	{
		if (*line == '%')
		{
			written_len = check_format(line + 1, info, &ap);
			line += written_len;
		}
		else
		{
			ft_putchar(*line, info);
			line++;
		}
	}
	va_end(ap);
	return (info->size);
}
#include<stdio.h>
int main()
{
	char	*s = "as";
	ft_printf("%p",s);
	printf("\n%p", s);
}
