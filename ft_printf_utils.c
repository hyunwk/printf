void	init_info(t_info *info)
{
	info->zero = 0;
	info->width = 0;
	info->left_align = 0;
	info->asterisk = 0;
	info->dot = -1;
	info->prec = -1;
}

void	get_flags(char c, t_info *info)
{
	if (c == '-')
		info->left_align = 1;
	if (c == '.')
		info->dot = 1;
	if (c == '0')
		info->zero = 1;
}

void	get_asterisk(t_info *info, va_list *ap)
{
	int	num;

	info->asterisk = 1;
	num = va_arg(*ap, int);
	if (num < 0)
	{
		if (info->dot == -1)
		{
			info->width = num * -1;
			info->left_align = 1;
		}
		else
		{
			info->asterisk = -1;
			info->dot = -1;
		}
	}
	else if (!info->width)
	{
		if (info->dot == -1)
			info->width = num;
		else
			info->prec = num;
	}
}

int	get_format_info(const char *line, t_info *info, va_list *ap)
{
	int	idx;

	idx = 0;
	if (line[idx] && '1' <= line[idx] && line[idx] <= '9')
		idx += is_num(&line[idx], info);
	while (ft_strchr(FLAG, line[idx]))
	{
		get_flags(line[idx], info);
		if ('*' == line[idx])
			get_asterisk(info, ap);
		idx++;
	}
	if (is_num(line + idx, info) && !info->asterisk)
		idx += is_num(line + idx, info);
	if (ft_strchr(TYPE, line[idx]) || line[idx] == '%')
		info->type = line[idx++];
	else
		return (ERR);
	return (idx);
}

int	check_format(const char *line, t_info *info, va_list *ap)
{
	int	rtn;

	init_info(info);
	rtn = get_format_info(line, info, ap);
	if (*line == '%')
		return (print_char('%', info) + rtn);
	if (rtn == ERR)
		return (ERR);
	if (info->type == 'c')
		return (print_char(va_arg(*ap, int), info) + rtn);
	if (info->type == 's')
		return (print_str(va_arg(*ap, char *), info) + rtn);
	if (info->type == 'p' || info->type == 'x' || info->type == 'X')
		return (print_hex(va_arg(*ap, unsigned long long), info) + rtn);
	if (info->type == 'd' || info->type == 'i')
		return (print_num(va_arg(*ap, int), info) + rtn);
	if (info->type == 'u')
		return (print_num((unsigned int)va_arg(*ap, int), info) + rtn);
	return (rtn);
}
