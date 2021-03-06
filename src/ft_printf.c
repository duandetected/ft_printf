/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:40:36 by alushenk          #+#    #+#             */
/*   Updated: 2017/02/09 16:40:40 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_len(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '%' && str[i])
		i++;
	return (i);
}

static size_t	do_print(t_format *f, va_list ap)
{
	if (f->type == 's' || f->type == 'S')
		write_string(f, ap);
	else if (f->type == 'c' || f->type == 'C')
		write_char(f, ap);
	else if (f->type)
	{
		write_num(f, ap);
		format_num_prefix(f);
		format_num(f);
	}
	format_string(f);
	ft_putstrn(f->prefix, f->prefix_len);
	ft_putstrn(f->sufix, f->sufix_len);
	return (f->prefix_len + f->sufix_len);
}

static void		parse(char **fmt, va_list ap, t_format *format)
{
	int		skip;

	skip = 0;
	while (**fmt)
	{
		if (check_type(fmt, format))
			break ;
		if ((skip = check_flags(fmt, format)) ||
			(skip = check_width(fmt, ap, format)) ||
			(skip = check_precision(fmt, ap, format)) ||
			(skip = check_size(fmt, format)))
			(*fmt) += skip;
		else
		{
			add_symbol(format, **fmt);
			(*fmt)++;
			break ;
		}
	}
}

static int		func(char *fmt, va_list ap, t_format **format)
{
	size_t	result;

	result = 0;
	while (*fmt)
	{
		initialise_struct(format);
		if (((*format)->prefix_len = get_len(fmt)))
		{
			(*format)->prefix = ft_strnew((*format)->prefix_len);
			ft_strncpy((*format)->prefix, fmt, (*format)->prefix_len);
		}
		fmt += (*format)->prefix_len;
		fmt = (*fmt) ? fmt + 1 : fmt;
		parse(&fmt, ap, *format);
		result += do_print(*format, ap);
	}
	return ((int)result);
}

int				ft_printf(char *fmt, ...)
{
	va_list		ap;
	t_format	*format;
	int			result;

	g_error = 0;
	format = NULL;
	va_start(ap, fmt);
	result = func(fmt, ap, &format);
	va_end(ap);
	if (result > INT_MAX || g_error)
		result = -1;
	if (format)
	{
		if (format->prefix)
			free(format->prefix);
		if (format->sufix)
			free(format->sufix);
		if (format->num_prefix)
			free(format->num_prefix);
		free(format);
	}
	return (result);
}
