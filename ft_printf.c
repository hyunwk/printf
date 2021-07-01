/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:53:14 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/01 17:45:03 by hyunwkim         ###   ########.fr       */
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
void	ft_putchar(char c)
{
	write(1, &c, 1);
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

void	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
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
	return (num);
}

void	init_info(s_info *info)
{
	info->zero = 0;
	info->width= 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int i;
	int len_src;

	if (!src)
		return (0);
	i = 0;
	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	while (i++ < dstsize - (int)1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len_src);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		idx;
	char	*ptr;

	if (!s1)
		return ((char *)s2);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	idx = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcpy(ptr + len_s1, s2, len_s2 + 1);
	return (ptr);
}

void	print_multi_str(char c, int time)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
		ft_putchar(c);
}

int		print_str(char *s, s_info *info)
{
	int space_len;

	space_len = info->width - ft_strlen(s);
	if (space_len >= 0)
		if (info->left_align)
		{
			ft_putstr(s);
			print_multi_str(' ', space_len); 
		}
		else
		{
			if (info->zero)
			{
				print_multi_str('0', space_len);
				ft_putstr(s);
			}
			else
			{
				print_multi_str(' ', space_len);
				ft_putstr(s);
			}
		}
	else
		ft_putstr(s);
	info->size += space_len + ft_strlen(s);
	return (1);
}

int		print_char(char c, s_info *info)
{
	ft_putchar(c);
	info->size += 1;
	return (sizeof(char));
}

int check_flags(const char *line, s_info *info, va_list *ap)
{
	int	num;
	int	idx;

	// flags  -0.*
	// check flags before num
	idx = 0;
	while (!is_num((line + idx), info) && !ft_strchr(FLAG_TYPE, line[idx]))
	{
		if (line[idx] == '-')
			info->left_align = 1;
		if (line[idx] == '.')
			info->dot = 1;
		if (line[idx] == '*')
		{
			num = va_arg(*ap, int);
			if (num < 0)
			{
				info->width = va_arg(*ap, int) * -1;
				info->left_align = 1;
			}
			else
				info->width = num;
			info->asterisk = 1;
		}
		idx++;
	}
	
	if (line[idx] == '0')
	{
		info->zero = 1;
		idx++;
	}
	// check width num
	if (is_num(&line[idx], info) && !info->asterisk)
	{
		info->width = is_num(&line[idx], info);
		// how to get int digit num
		idx += ft_strlen(info->width);
	}

	// check flag_type ,   what if err?
	if (ft_strchr(FLAG_TYPE, line[idx]))
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
		ft_putchar('%');
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
			ft_putchar(*line);
			info->size++;
			line++;
		}
	}
	va_end(ap);
	return (info->size);
}

int main()
{
	int rtn;

//	rtn = ft_printf("%-6s\n","12");
//	printf("s + '\\n'  len : %d\n",rtn);
//	rtn = ft_printf("%6s\n","12");
//	printf("s + '\\n'  len : %d\n",rtn);
	rtn = ft_printf("%12s\n","12");
	printf("\nanswer : %12s\n","12");
	printf("s + '\\n'  len : %d\n",rtn);
	//rtn = ft_printf("%d\n",12);
	//printf("return len : %d\n",rtn);
}

