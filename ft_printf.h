/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:00:07 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/08 18:48:12 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define ERR -1
# define TYPE "cspdiuxX%"

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

int		ft_printf(const char *line, ...);
int		check_format(const char *line, va_list ap, int *rtn);
int		print_hex(unsigned long long n, char type, int *rtn);
int		print_str(char *s, int *rtn);
int		print_nbr(long long n, char type, int *rtn);
int		get_hex_digits(unsigned long long n);
char	*get_base(char c);
void	ft_putchar(char c, int *rtn);
void	ft_putstr(char *s, int *rtn);

#endif
