/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:05:45 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/01 19:22:27 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

int			ft_strlen(char *s);
void		ft_putchar(char c);
char		*ft_strchr(const char *s, int c);
void		ft_putstr(char *s, int time);
int			ft_strlcpy(char *dst, char *src, int dstsize);
char		*ft_strjoin(char *s1, char *s2);

#endif
