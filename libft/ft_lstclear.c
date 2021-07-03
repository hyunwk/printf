/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:04:51 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/05/19 18:46:33 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*n;

	temp = *lst;
	while (temp)
	{
		n = temp->next;
		ft_lstdelone(temp, (*del));
		temp = n;
	}
	*lst = NULL;
}
