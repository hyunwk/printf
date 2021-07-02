/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 16:22:07 by hyunwkim         ###   ########.fr       */
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
void	ft_putchar(char c, s_info *info)
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

void	ft_putstr(char *s, int time, s_info *info)
{
	int idx;

	idx = 0;
	while (idx < time)
	{
		ft_putchar(*s, info);
		s++;
		idx++;
	}
}

int	is_num(const char *s, s_info *info)
{
	int idx;
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
		info->precise = num;
	return (idx);
}

void	init_info(s_info *info)
{
	info->zero = 0;
	info->width= 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	info->precise = -1; // dot and precise duplicated
}

void	print_multi_str(char c, int time, s_info *info)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
		ft_putchar(c, info);
}

int		print_str(char *s, s_info *info)
{
	int space_len;

	space_len = ft_strlen(s) - info->width ;
	// len > width
	if (space_len >= 0 && info->dot != -1 && ft_strlen(s) > info->precise)
	{
		if (info->width > info->precise)
			print_multi_str(' ', info->width - info->precise, info);
		ft_putstr(s, info->precise, info);
	}
	else if (space_len >= 0 && (ft_strlen(s) <= info->precise || info->precise == -1))
		ft_putstr(s, ft_strlen(s), info);
	// width > len
	else
	{
		if (info->left_align)
		{
			ft_putstr(s, ft_strlen(s), info);
			print_multi_str(' ', info->width - ft_strlen(s), info); 
		}
		else
		{
			if (info->zero)
			{
				print_multi_str('0', info->width - ft_strlen(s), info);
				ft_putstr(s, ft_strlen(s), info);
			}
			else
			{
				print_multi_str(' ', info->width - ft_strlen(s), info);
				ft_putstr(s, ft_strlen(s), info);
			}
		}
	}
	return (1);
//	if (ft_strlen(s) >= info->width)
//		ft_putstr(s, ft_strlen(s));
//	else if (ft_strlen(s) > info->precise && info->width > info->precise)
//	{
//		print_multi_str(' ', info->width - info-> precise);
//		ft_putstr(s, info->precise);
//	}
//	else if (ft_strlen(s) > info->precise)
//		ft_putstr(s, info->precise);
//	else if (ft_strlen(s) < info->precise && ft_strlen(s) < info->width)
//	{
//		print_multi_str(' ', info->width - ft_strlen(s));
//		ft_putstr(s, ft_strlen(s));
//	}
//	else
//	{
//		if (info->left_align)
//		{
//			ft_putstr(s, ft_strlen(s));
//			print_multi_str(' ', info->width - ft_strlen(s));
//		}
//		else
//		{
//			print_multi_str(' ', info->width - ft_strlen(s));
//			ft_putstr(s, ft_strlen(s));
//		}
//	}
//	return (1);
}

int		print_char(char c, s_info *info)
{
	ft_putchar(c, info);
	info->size += 1;
	return (sizeof(char));
}
void	check_precision(char c, s_info *info, va_list *ap)
{
	int	num;

	if (c == '-')
		info->left_align = 1;
	if (c  == '.')
		info->dot = 1;
	if (c == '0')
		info->zero = 1;
	if (c == '*')
	{
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
				info->precise = num;
		}
	}
}

int check_flags(const char *line, s_info *info, va_list *ap)
{
	int	idx;

	idx = 0;
	//width
	if (is_num(&line[idx], info))
		idx += is_num(&line[idx], info);

	// flag
	while (ft_strchr(FLAG, line[idx]))
		check_precision(line[idx++], info, ap);

	// check precise
	if (is_num(line + idx, info) && !info->asterisk)
		idx += is_num(line + idx, info);

	// check flag_type ,   what if err?
	if (ft_strchr(TYPE, line[idx]))
		info->type = line[idx++];
	else
		return (ERR);
	return (idx);
}

int	check_format(const char *line, s_info *info, va_list *ap)
{
	int rtn;

	init_info(info);
	rtn = check_flags(line, info, ap);
	if (*line == '%')
		ft_putchar('%', info);
	else if (info->type == 'c')
		return (print_char(va_arg(*ap, int), info) + rtn);
	else if (info->type == 's')
		return (print_str((char *)va_arg(*ap, char *), info) + rtn);
//	else if (info->type == 'p')
//		return (print_str((long long)va_arg(*ap, long long), info) + rtn);
//	else if (info->type == 'd')
//		return (print_str(va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'i')
//		return (print_str(va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'u')
//		return (print_str((unsigned int)va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'x')
//		return (print_str((unsigned int)va_arg(*ap, int), info) + rtn);
//	else if (info->type == 'X')
//		return (print_str((unsigned int)va_arg(*ap, int), info) + rtn);
	return (rtn);
}

int ft_printf(const char *line, ...)
{
	va_list ap;
	s_info	*info;
	int		written_len;

	va_start(ap, line);

	if (!(info = malloc(sizeof(s_info) * 1)))
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

int main()
{
	int result_f, result_r;
	char *s = "42Seoul";
	printf("case1\n");
	result_f = ft_printf("-->|%-12s|<--\n", s);
	result_r =    printf("-->|%-12s|<--\n", s);
	printf("result_f = %d\nresult_r = %d\n\n", result_f, result_r);
}
