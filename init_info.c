/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:18:51 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/03 16:14:34 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_info(t_info *info)
{
	info->zero = 0;
	info->width = 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	info->prec = -1;
}
