/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:21:10 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 15:22:29 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	s_len;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(""));
	s_len = ft_strlen(s + start);
	if (s_len > len)
		s_len = len;
	if (!(ptr = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
