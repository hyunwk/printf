/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:15:01 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/05/19 18:50:32 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			idx;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	idx = 0;
	while (idx < n)
	{
		if (p1[idx] != p2[idx])
			return (p1[idx] - p2[idx]);
		idx++;
	}
	return (0);
}
