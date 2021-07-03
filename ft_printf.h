/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:00:07 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/03 16:50:55 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#define ERR -1
#define TYPE "cspdiuxX"
#define FLAG "-0.*"

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct s_info
{
	char	type;
	int		size;
	int		zero;
	int		width;
	int		prec;
	int		left_align;
	int		asterisk;
	int		dot;
}	t_info;

int		ft_printf(const char *line, ...);
int		check_format(const char *line, t_info *info, va_list *ap);
int		get_format_info(const char *line, t_info *info, va_list *ap);
void	get_asterisk(t_info *info, va_list *ap);
void	get_flags(char c, t_info *info);
void	init_info(t_info *info);
int		print_num(int n, t_info *info);
int		get_int_digits(int n);
int		is_minus(int n);
int		is_num(const char *s, t_info *info);
int		print_hex(unsigned long long n, t_info *info);
char	*get_base(char c);
int		print_char(char c, t_info *info);
int		print_str(char *s, t_info *info);
void	print_multi_str(int time, t_info *info);
void	ft_putchar(char c, t_info *info);
void	ft_putstr(char *s, int time, t_info *info);
int		ft_putnbr(int n, t_info *info);
#endif
