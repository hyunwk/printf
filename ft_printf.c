/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/14 17:43:33 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void	get_flags(char c, t_info *info)
{
	if (c == '-')
		info->left_align = 1;
	if (c == '.')
		info->dot = 1;
	if (c == '0' && info->dot == -1)
		info->zero = 1;
}

void	get_asterisk(t_info *info, va_list *ap)
{
	int	num;

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

int	get_format_info(const char *line, t_info *info, va_list *ap)
//int	get_format_info(const char *line, t_info *info)
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
		get_flags(line[idx], info);
		
		if ('*' == line[idx++])
			get_asterisk(info, ap);
	}
	if ('0' <= line[idx] && line[idx] <= '9' && !info->asterisk)
		idx += is_num(line + idx, info);
	if (ft_strchr(TYPE, line[idx]) || line[idx] == '%')
		info->type = line[idx++];
	else
		return (ERR);
	return (idx);
}

int	check_format(const char *line, t_info *info, va_list *ap)
{
	int	rtn;

	init_info(info);
	rtn = get_format_info(line, info, ap);
	//rtn = get_format_info(line, info);
	if (info->type == '%')
		return (print_char('%', info) + rtn);
	if (rtn == ERR)
		return (ERR);
	if (info->type == 'c')
		return (print_char(va_arg(*ap, int), info) + rtn);
	if (info->type == 's')
		return (print_str(va_arg(*ap, char *), info) + rtn);
	//if (info->type == 'p' || info->type == 'x' || info->type == 'X')
	if (info->type == 'p')
		return (parse_hex(va_arg(*ap, unsigned long long), info) + rtn);
	if (info->type == 'x' || info->type == 'X')
		return (parse_hex(va_arg(*ap, unsigned int), info) + rtn);
	if (info->type == 'd' || info->type == 'i')
		return (print_num(va_arg(*ap, int), info) + rtn);
	if (info->type == 'u')
		return (print_num((unsigned int)va_arg(*ap, int), info) + rtn);
	return (rtn);
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
			written_len = check_format(format + 1, info, &ap);
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

int	print_str(char *s, t_info *info)
{
	if (!s)
		s = ft_strdup("(null)");
	if ((int)ft_strlen(s) >= info->width && info->width > 0)
	{
		if (info->dot == 1 && info->width > info->prec && !info->left_align)
			print_multi_str(info->width - info->prec, info);

		if (info->prec <= (int)ft_strlen(s) && info->dot == 1)
			ft_putstr(s, info->prec, info);

		else
			ft_putstr(s, ft_strlen(s), info);
		
		if (info->dot == 1 && info->width > info->prec && info->left_align)
			print_multi_str(info->width - info->prec, info);
	} 
	else 
	{
//		print_str_bigger_width(s, info);
		if (info->width > (int)ft_strlen(s))
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
		else
		{
			if ((int)ft_strlen(s) > info->prec && info->dot == 1 )
				ft_putstr(s, info->prec, info);
			else
				ft_putstr(s, ft_strlen(s), info);
		}
	}
	if (!ft_strncmp(s,"(null)", 6))
		free(s);
	return (1);
}

int	get_int_digits(int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
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

int	is_minus(int n)
{
	return (n < 0);
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

void	print_multi_str(int time, t_info *info)
{
	int		idx;
	char	c;

	idx = 0;
	if (info->zero)
		c = '0';
	else
		c = ' ';
	while (idx++ < time)
		ft_putchar(c, info);
}

int	print_num(long long n, t_info *info)
{
	if (info->left_align)
	{
		if (info->width > info->prec && info->prec > get_int_digits(n))
		{
			if (is_minus(n))
			{
				ft_putchar('-', info);
				n *= -1;
				info->width -= 1;
			}
			info->zero = 1;
			print_multi_str(info->prec - get_int_digits(n), info);
			ft_putnbr(n, info);
			info->zero = 0;
			print_multi_str(info->width - info->prec, info);
		}
		else if (info->width > get_int_digits(n) && get_int_digits(n) > info->prec)
		{
			if (!n && info->dot != -1)
				print_multi_str(info->width - get_int_digits(n) + 1, info);
			else
			{
				ft_putnbr(n, info);
				print_multi_str(info->width - get_int_digits(n), info);
			}
		}
		else if (info->prec >= info->width ||  info->prec > get_int_digits(n))
		{
			if (is_minus(n))
			{
				ft_putchar('-', info);
				n *= -1;
			}
			if (get_int_digits(n) > info->width)
				info->zero = 1;
			print_multi_str(info->prec - get_int_digits(n), info);
			if (n)
				ft_putnbr(n, info);
		}
		else 
			ft_putnbr(n, info);
	}
	else 
	{
		//if (info->prec > get_int_digits(n))
		if (info->prec >= get_int_digits(n))
		{
			if (info->width > info->prec)
			{
				info->zero = 0;
				print_multi_str(info->width - info->prec - is_minus(n), info);
			}
			if (is_minus(n))
			{
				ft_putchar('-', info);
				n *= -1;
			}
			info->zero = 1;
			print_multi_str(info->prec - get_int_digits(n), info);
		}
		else if (info->prec >= info->width && info->width > get_int_digits(n))
			print_multi_str(info->prec - get_int_digits(n), info);
		else if (info->width > get_int_digits(n) && get_int_digits(n) > info->prec)
		{
			if (is_minus(n) && info->zero && info->dot == -1)
			{
				ft_putchar('-', info);
				n *= -1;
				info->width -= 1;
			}
			if (info->dot == -1 && info->zero)
				info->zero = 1;
			else
				info->zero = 0;
			if (!n && info->dot != -1)
				print_multi_str(info->width - get_int_digits(n) + 1, info);
			else
				print_multi_str(info->width - get_int_digits(n), info);
		}
		if (n || info->prec > 0 || info->dot != 1)
			ft_putnbr(n, info);
	}
	return (1);
}

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

char	*get_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

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
	{
		hex_arr[0] = '0';
		hex_arr[1] = 'x';
		hex_arr[2] = '0';
	}
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
int	print_hex(char *s, t_info *info)
{
	if (info->left_align)
	{
		if (info->width > info->prec && info->prec > (int)ft_strlen(s))
		{
			info->zero = 1;
			print_multi_str(info->prec - (int)ft_strlen(s), info);
			ft_putstr(s, (int)ft_strlen(s), info);
			info->zero = 0;
			print_multi_str(info->width - info->prec, info);
		}
		else if (info->width > (int)ft_strlen(s) && (int)ft_strlen(s) > info->prec)
		{
			if (s[0] - '0' == 0 && info->dot == 1)
				print_multi_str(info->width, info);
			else
			{
				ft_putstr(s, (int)ft_strlen(s), info);
				print_multi_str(info->width - (int)ft_strlen(s), info);
			}
		}
		else if (info->prec >= info->width ||  info->prec > (int)ft_strlen(s))
		{
			if ((int)ft_strlen(s) > info->width)
				info->zero = 1;
			print_multi_str(info->prec - (int)ft_strlen(s), info);
			if (s[0] - '0' != 0)
				ft_putstr(s, (int)ft_strlen(s), info);
			else if (s[1] == 'x')
				ft_putstr("0x", 2, info);
		}
		else 
			ft_putstr(s, (int)ft_strlen(s), info);
	}
	else 
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
			if (info->dot == -1 && info->zero)
				info->zero = 1;
			else
				info->zero = 0;
			if (s[0] - '0' == 0 && info->dot == 1 && info->type == 'p')
				print_multi_str(info->width - 2, info);
			else if (s[0] - '0' == 0 && info->dot == 1)
				print_multi_str(info->width, info);
			else
				print_multi_str(info->width - (int)ft_strlen(s), info);
		}
		if (info->prec > 0 || info->dot != 1 || (info->type == 'p' && ft_strncmp(s,"0x0",3)))
			ft_putstr(s, (int)ft_strlen(s), info);
		else if (info->type == 'p')
			ft_putstr("0x", 2, info);
	}
	return (1);
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

void	ft_putnbr(long long n, t_info *info)
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
}
//#include<stdio.h>
//int main()
//{
//	ft_printf("%-.p\n",NULL);
//	printf("%-.p\n",NULL);
//	ft_printf("%-.s\n","");
//	printf("%-.s\n","");
//	ft_printf("%-.d\n",0);
//	printf("%-.d\n",0);
//	ft_printf("%-.u\n",0);
//	printf("%-.u\n",0);
//	ft_printf("%-.x\n",0);
//	printf("%-.x\n",0);
//	ft_printf("%-.X\n",0);
//	printf("%-.X\n",0);
//}
