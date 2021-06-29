/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/29 16:50:39 by hyunwkim         ###   ########.fr       */
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
void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
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

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	is_num(char *s, s_info *info)
{
	int idx;
	int	num;
	
	idx = 0;
	num = 0;
	while ('0' <= s[idx] && s[idx] <= '9')
		num = num * 10 + *line - '0';
	info->width_len = idx;
	return (num);
}

int check_flags(char *line, s_info *info)
{
	int	num;
	int	idx;

	// flags  -0.*
	// check flags before num
	idx = 0;
	while (!is_num(line[idx], info) && !ft_strchr(FLAG_ALPHA, line[idx]))
	{
		if (line[idx] == '-')
			info->right_align = 0;
		if (line[idx] == '*')
			info->asterisk = 1;
		idx++;
	}
	
	// check width num
	info->width = is_num(line[idx++], info);

	// check flag_alpha ,   what if err?
	info->alpha = line[idx++];
	return (idx);
}

void	init_info(s_info *info)
{
	info->zero = 0;
	info->width_num= 0;
	info->right_align = 1;
	info->asterisk = 0;
	info->dot = 0;
}

int	check_format(const char *line, s_info *info, va_list *ap)
{
	int len;
	int rtn;
	char	*s;

	init_info(info);
	rtn = check_flags(*line)

	len = 0;
	if (*line == '%')
		ft_putchar('%', 1);
	else if (info->alpha == 's')
	{
		// write without any flags
		s = (char *)va_arg(*ap, char *);
		write(1, s, ft_strlen(s));
		info->size += ft_strlen(s);
		return (ft_strlen(s));
	}
	// need to add conversion  cspdiuxX%
	return (len);
}

int		is_valid(const char *line, va_list ap)
{
	return (0);
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

	if (is_valid(line, ap))
		return (ERR);

	while (*line)
	{
		if (*line == '%')
		{
			written_len = check_format(line + 1, info, &ap);
			line += written_len;
		}
		else
		{
			ft_putchar(*line, 1);
			info->size++;
			line++;
		}
	}

	va_end(ap);
	return (info->size);
}

int main()
{
	int rtn = ft_printf("%s %s\n","12", "abc");
	printf("return len : %d",rtn);
}

