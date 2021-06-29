/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:00:07 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/29 16:41:10 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#define ERR -1
#define FLAG_ALPHA "cspdiuxX"

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct st_info
{
	int	size; // printf return len
	int	zero; // flag zero
	int	width_num; // flag width size
	int right_align;
	int	asterisk; // flag *
	int	dot;      // flag .
} s_info;
#endif
