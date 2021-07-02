/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunwkim <hyunwkim@42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:14:00 by hyunwkim          #+#    #+#             */
/*   Updated: 2021/07/02 22:14:01 by hyunwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_multi_str(int time, t_info *info)
{
	int		idx;
	char	c;

	idx = 0;
	if (info->zero && !info->left_align)
		c = '0';
	else
		c = ' ';
	while (idx++ < time)
		ft_putchar(c, info);
}

int	print_str(char *s, t_info *info)
{
	int	space_len;

	space_len = ft_strlen(s) - info->width ;
	if (!s)
		return (ERR);
	if (space_len >= 0 && info->dot != -1 && ft_strlen(s) > info->prec)
	{
		if (info->width > info->prec)
			print_multi_str(info->width - info->prec, info);
		ft_putstr(s, info->prec, info);
	}
	else if (space_len >= 0 && (ft_strlen(s) <= info->prec || info->prec == -1))
		ft_putstr(s, ft_strlen(s), info);
	else if (info->left_align)
	{
		ft_putstr(s, ft_strlen(s), info);
		print_multi_str(info->width - ft_strlen(s), info);
	}
	else
	{
		print_multi_str(info->width - ft_strlen(s), info);
		ft_putstr(s, ft_strlen(s), info);
	}
	return (1);
}

int	print_char(char c, t_info *info)
{
	if (info->left_align)
	{
		ft_putchar(c, info);
		if (info->width)
			print_multi_str(info->width - 1, info);
	}
	else
	{
		if (info->width)
			print_multi_str(info->width - 1, info);
		ft_putchar(c, info);
	}
	return (1);
}

char	*get_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}

int	print_hex(unsigned long long n, t_info *info)
{
	char	*hex_arr;
	int		i;

	i = 8;
	hex_arr = (char *)malloc(sizeof(char) * 9);
	if (!hex_arr)
		return (ERR);
	if (info->type == 'p' || info->type == 'x')
		ft_putstr("0x", 2, info);
	else if (info->type == 'X')
		ft_putstr("0X", 2, info);
	while (n)
	{
		hex_arr[i--] = get_base(info->type)[n % 16];
		n /= 16;
	}
	print_str(hex_arr, info);
	free(hex_arr);
	return (1);
}
