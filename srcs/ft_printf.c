/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/20 02:47:03 by hyunwkim         ###   ########.fr       */
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
	else
		return (ERR);
	return (idx + 1);
}

int	check_format(const char *line, t_info *info, va_list *ap)
{
	int	rtn;

	init_info(info);
	rtn = get_format_info(line, info);
	if (rtn == ERR)
		return (1);
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
