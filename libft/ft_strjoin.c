/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:58:29 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/01 15:59:55 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		idx;
	char	*ptr;

	if (!s1)
		return ((char *)s2);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	idx = 0;
	ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcpy(ptr + len_s1, s2, len_s2 + 1);
	return (ptr);
}
