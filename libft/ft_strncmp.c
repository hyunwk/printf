/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:14:08 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 14:56:46 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			cnt;
	unsigned char	*unsign_s1;
	unsigned char	*unsign_s2;

	if (!n)
		return (0);
	unsign_s1 = (unsigned char *)s1;
	unsign_s2 = (unsigned char *)s2;
	cnt = 0;
	while (*unsign_s1 == *unsign_s2 && *unsign_s1 && *unsign_s2 && cnt < n)
	{
		cnt++;
		unsign_s1++;
		unsign_s2++;
	}
	if (cnt == n)
		return (*(--unsign_s1) - *(--unsign_s2));
	return (*unsign_s1 - *unsign_s2);
}
