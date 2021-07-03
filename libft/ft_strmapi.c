/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:37:55 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/05/20 19:09:21 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	char			*ptr;

	idx = 0;
	if (!s || !f)
		return (0);
	if (!(ptr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[idx])
	{
		ptr[idx] = (*f)(idx, s[idx]);
		idx++;
	}
	ptr[idx] = 0;
	return (ptr);
}
