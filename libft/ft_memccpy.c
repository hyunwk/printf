/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:35:42 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/05/20 18:19:10 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t idx;

	idx = 0;
	if (!src && !dst)
		return (NULL);
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = ((unsigned char*)src)[idx];
		if (((unsigned char *)src)[idx] == (unsigned char)c)
			return (dst + idx + 1);
		idx++;
	}
	return (0);
}
