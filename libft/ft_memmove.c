/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:48:17 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 14:40:33 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*unsigned_dst;
	unsigned char	*unsigned_src;
	size_t			i;

	unsigned_dst = (unsigned char*)dst;
	unsigned_src = (unsigned char*)src;
	i = 0;
	if (!src && !len)
		return (dst);
	while (dst < src && i < len)
	{
		unsigned_dst[i] = unsigned_src[i];
		i++;
	}
	while (src < dst && i < len)
	{
		unsigned_dst[len - i - 1] = unsigned_src[len - i - 1];
		i++;
	}
	return (dst);
}
