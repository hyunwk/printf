/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 21:32:47 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/19 16:52:28 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	if (!src)
		return (0);
	i = 0;
	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	while (i++ < dstsize - (size_t)1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len_src);
}
