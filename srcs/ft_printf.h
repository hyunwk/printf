/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:00:07 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 18:21:12 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define ERR -1
# define TYPE "cspdiuxX"
# define FLAG "-0."

# include <stdarg.h>
# include "../libft/libft.h"

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

// ft_printf.c
int		ft_printf(const char *line, ...);
int		check_format(const char *line, t_info *info, va_list *ap);
int		get_format_info(const char *line, t_info *info);
void	get_flags(char c, t_info *info);
void	init_info(t_info *info);

// print_str.c 
int		print_char(char c, t_info *info);
int		print_str(char *s, t_info *info);
void	print_str_bigger_len(char *s, t_info *info);
void	print_str_bigger_width(char *s, t_info *info);

// print_num.c
int		print_num(long long n, t_info *info);
int		print_num_left_bigger_width(long long *n, t_info *info);
int		print_num_left_else(long long *n, t_info *info);
int		print_num_right_bigger_prec(long long *n, t_info *info);
int		print_num_right_else(long long *n, t_info *info);

// print_hex.c
int		print_hex(char *s, t_info *info);
int		print_hex_left(char *s, t_info *info);
void	print_hex_left_else(char *s, t_info *info);
void	print_hex_right(char *s, t_info *info);

// num_utils.c
int		get_num_len(long long n);
int		is_minus(int n);
int		is_num(const char *s, t_info *info);

// hex_uitls.c 
int		parse_hex(unsigned long long n, t_info *info);
char	*get_base(char c);
int		get_hex_len(unsigned long long n);

// print_utils.c
void	ft_putchar(char c, t_info *info);
void	ft_putstr(char *s, int time, t_info *info);
void	ft_putnbr(long long n, t_info *info);
void	print_multi_str(int time, t_info *info);

#endif
