/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:00:07 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/01 20:44:38 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#define ERR -1
#define FLAG_TYPE "cspdiuxX"

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

typedef struct st_info
{
	char	type;
	int		size; // printf return len
	int		zero; // flag zero
	int		width; // flag width size
	int		precise; // flag precise 
	int		left_align;
	int		asterisk; // flag *
	int		dot;      // flag .
} s_info;

#endif
