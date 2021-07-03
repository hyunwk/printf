
// width, strlen, prec, left_align
// len > width  && width is not 0
if ((int)ft_strlen(s) >= info->width && !info->width)
{
	// width > prec, then print_multi_line
	if (info->prec != -1 && info->width - info->prec > 0)
		print_multi_str(info->width - info->prec, info);
	// 0 <= prec <= len
	if (0 <= info->prec && info->prec <= (int)ft_strlen(s))
		ft_putstr(s, info->prec, info);
	else
		ft_putstr(s, ft_strlen(s), info);
} 
// no width   or width > len
else 
{
	if (info->width > (int)ft_strlen(s))
	{
		if (info->prec < (int)ft_strlen(s))
		{
			print_multi_str(info->width - info->prec, info);
			ft_putstr(s, info->prec, info);
		}
		else
		{
			print_multi_str(info->width - (int)ft_strlen(s), info);
			ft_putstr(s, (int)ft_strlen(s), info);
		}
	}
	else
	{
		ft_putstr(s, ft_strlen(s), info);
	}
}
