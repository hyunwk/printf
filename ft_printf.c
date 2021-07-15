/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/15 20:03:00 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
//int	get_format_info(const char *line, t_info *info)
int	get_format_info(const char *line, t_info *info, va_list *ap)
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
		//get_flags(line[idx++], info);
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
	//rtn = get_format_info(line, info);
	rtn = get_format_info(line, info, ap);
	if (info->type == '%')
		return (print_char('%', info) + rtn);
	if (rtn == ERR)
		return (ERR);
	if (info->type == 'c')
		return (print_char(va_arg(*ap, int), info) + rtn);
	if (info->type == 's')
		return (print_str(va_arg(*ap, char *), info) + rtn);
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

void	init_info(t_info *info)
{
	info->zero = 0;
	info->width = 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	info->prec = 0;
}

//#include<stdio.h>
//int main()
//{
//	ft_printf("%s%s\n", "abc","def");
//	printf("%s%s\n", "abc","def");
//	ft_printf("%5.0i.\n", 0);
//	printf("%5.0i.\n", 0);
//	ft_printf("%p\n", NULL);
//	printf("%p\n", NULL);
//	ft_printf("%p\n", "Abc");
//	printf("%p\n", "Abc");
//	ft_printf("%-1.1d.\n",0);
//	printf("%-1.1d.\n",0);
//	ft_printf("%-.d.\n",0);
//	printf("%-.d.\n",0);
//	ft_printf("%-.d.\n",0);
//	printf("%-.d.\n",0);
//
//	ft_printf("%-.0d.\n",0);
//	printf("%-.0d.\n",0);
//
//
//	ft_printf("%-.1d.\n",0);
//	printf("%-.1d.\n",0);
//
//
//	ft_printf("%-1.d.\n",0);
//	printf("%-1.d.\n",0);
//	ft_printf("%-d\n",0);
//	printf("%-d\n",0);
//	ft_printf("%1.d.\n",0);
//	printf("%1.d.\n",0);
//}
