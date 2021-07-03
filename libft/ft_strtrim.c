/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:00:16 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/06/08 16:42:22 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t		front;
	size_t		rear;

	if (!s1 || !set)
		return (0);
	front = 0;
	rear = ft_strlen(s1) - 1;
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	if (front == rear + 1)
		return (ft_strdup(""));
	while (s1[rear] && ft_strchr(set, s1[rear]))
		rear--;
	if (front >= rear)
		return (ft_strdup(""));
	return (ft_substr(s1, front, rear - front + 1));
}
