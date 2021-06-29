/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/29 15:46:36 by hyunwkim         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

//int check_info(char *line, s_info *info)
//{
//	int	num;
//	int	idx;
//
//	while ('0' <= *line && *line <= '9')
//	{
//		num = *line - '0';
//		if (num == 0 && info->right_align)
//			
//	}
//	// info   -0.*
//	if (*line == '-')
//
//}
//

void	init_info(s_info *info)
{
	info->width = 0;
	info->right_align = 1;
}
int	check_format(const char *line, s_info *info, va_list *ap)
{
	int len;
	char	*s;
	// conversion  cspdiuxX%
//	if (check_info(*line))
//
	init_info(info);
	len = 0;
	if (*line == '%')
		ft_putchar('%', 1);
	else if (*line == 's')
	{
		s = (char *)va_arg(*ap, char *);
		//write(1, s, ft_strlen(s));
		write(1, s, ft_strlen(s));
		info->size += ft_strlen(s);
		return (ft_strlen(s));
	}
	return (len);
}
int ft_printf(const char *line, ...)
{
	va_list ap;
	s_info	*info;
	int		written_len;

	va_start(ap, line);
	info->size = 0;
	// 유효성 검사하는 함수
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

