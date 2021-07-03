/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:32:06 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/05/21 17:44:17 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (ptr - len);
}
