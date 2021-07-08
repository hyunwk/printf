/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/08 18:45:26 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		rtn;
	int		written_len;

	va_start(ap, format);
	rtn = 0;
	while (*format)
	{
		if (*format == '%')
		{
			written_len = check_format(format + 1, ap, &rtn);
			if (written_len == -1)
				return (ERR);
			format += written_len;
		}
		else
		{
			ft_putchar(*format, &rtn);
			format++;
		}
	}
	va_end(ap);
	return (rtn);
}

int	check_format(const char *line, va_list ap, int *rtn)
{
	char	type;

	if (ft_strchr(TYPE, line[0]))
		type = line[0];
	else
		return (ERR);
	if (type == '%')
		ft_putchar('%', rtn);
	else if (type == 'c')
		ft_putchar(va_arg(ap, int), rtn);
	else if (type == 's')
		print_str(va_arg(ap, char *), rtn);
	else if (type == 'p' )
		print_hex(va_arg(ap, unsigned long long), type, rtn);
	else if (type == 'x' || type == 'X')
		print_hex(va_arg(ap, unsigned int), type, rtn);
	else if (type == 'd' || type == 'i')
		print_nbr(va_arg(ap, int), type, rtn);
	else if (type == 'u')
		print_nbr(va_arg(ap, unsigned int), type, rtn);
	return (2);
}

int	print_hex(unsigned long long n, char type, int *rtn)
{
	char	*hex_arr;
	int		hex_len;

	hex_len = get_hex_digits(n);
	hex_arr = (char *)malloc(sizeof(char) * (hex_len + 1));
	if (!hex_arr)
		return (ERR);
	if (type == 'p')
		ft_putstr("0x", rtn);
	if (n)
	{
		hex_arr[hex_len] = 0;
		while (n)
		{
			hex_arr[--hex_len] = get_base(type)[n % 16];
			n /= 16;
		}
		print_str(hex_arr, rtn);
	}
	else
		ft_putchar('0', rtn);
	free(hex_arr);
	return (1);
}

int	print_str(char *s, int *rtn)
{
	if (!s)
		s = ft_strdup("(null)");
	ft_putstr(s, rtn);
	if (!ft_strncmp(s, "(null)", 6))
		free(s);
	return (2);
}

int	print_nbr(long long n, char type, int *rtn)
{
	long long	temp;

	temp = n;
	if (type == 'd' && (temp < -2147483648 || temp > 2147483648))
		return (0);
	else if (type == 'u' && (temp < 0 || temp > 4294967295))
		return (0);
	if (temp < 0)
	{
		ft_putchar('-', rtn);
		temp = -temp;
	}
	if (temp >= 10)
	{
		print_nbr(temp / 10, type, rtn);
		ft_putchar(temp % 10 + '0', rtn);
	}
	if (temp < 10)
		ft_putchar(temp % 10 + '0', rtn);
	return (1);
}
