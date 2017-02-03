//
// Created by Anton Lushenko on 1/12/17.
//

#include "ft_printf.h"

int skip_atoi(char **s)
{
	size_t i;

	i = 0;
	while (ft_isdigit(**s))
	{
		i = i * 10 + *((*s)++) - '0';
		if (i > INT_MAX)
			return (INT_MAX);
	}
	return ((int) i);
}

void initialise_struct(t_format **format)
{
	/*
	 * продумать значения по умолчанию, как себя ведет прога если они остаются неизмененными.
	 * как поведут себя функции check_ если эти значения изменить
	 *
	 * нету смысла фришить сам поинтер на структуру, можно тупо его обнулять
	 */
	if (!*format)
	{
		*format = (t_format *) malloc(sizeof(t_format));
		(*format)->prefix = NULL;
		(*format)->sufix = NULL;
	}
	(*format)->flag = 0;
	(*format)->width = 0;
	(*format)->precision = -1;
	(*format)->size = 0;
	(*format)->type = 0;
	(*format)->prefix_len = 0;
	(*format)->sufix_len = 0;
	(*format)->base = 10;
	if ((*format)->prefix)
		free((*format)->prefix);
	(*format)->prefix = NULL;
	if ((*format)->sufix)
		free((*format)->sufix);
	(*format)->sufix = NULL;
}

int check_flags(char **fmt, t_format *format)
{
	if (**fmt == '-')
		format->flag |= LEFT;
	else if (**fmt == '+')
		format->flag |= PLUS;
	else if (**fmt == ' ')
		format->flag |= SPACE;
	else if (**fmt == '#')
		format->flag |= HASH;
	else if (**fmt == '0')
		format->flag |= ZEROPAD;
	else
		return (0);
	return (1);
}

int check_width(char **fmt, va_list ap, t_format *format)
{
	if (**fmt == '*')
	{
		(*fmt)++;
		format->width = (int) va_arg (ap, int);
		if (format->width < 0)
		{
			format->flag |= 1;
			//не творит ли оно хуню с минимальным интом?
			//если творит, то творит ли оригинальный принтф такую же хуйню?
			format->width = -format->width;
		}
	}
	else if (ft_isdigit(**fmt) && (format->width = skip_atoi(fmt)))
		return (1);
	return (0);
}

int check_precision(char **fmt, va_list ap, t_format *format)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		if (**fmt == '*')
		{
			(*fmt)++;
			format->precision = (int) va_arg (ap, int);
			if (format->precision < 0)
				format->precision = 0;
			return (1);
		}
		else if ((format->precision = skip_atoi(fmt)))
			return (1);
	}
	return (0);
}

int check_size(char **fmt, t_format *format)
{
	size_t len;

	len = 1;
	/*
	 * важно чтобы сначала шли проверки на два символа, иначе при 'l' не зайдет в 'll'
	 *
	 * "&&" в ифах - мастерство укорачивать код костылями
	 *
	 * как оно себя ведет при считывании hhh или lll (сейчас работает только с одной и двумя)
	 */
	if (**fmt == 'z')
		format->size |= Z;
	else if (**fmt == 'j')
		format->size |= J;
	else if (!strncmp(*fmt, "ll", 2) && len++)
		format->size |= LL;
	else if (**fmt == 'l')
		format->size |= L;
	else if (!strncmp(*fmt, "hh", 2) && len++)
		format->size |= HH;
	else if (**fmt == 'h')
		format->size |= H;
	else
		return (0);
	(*fmt) += len;
	return (1);
}

void check_type(char **fmt, t_format *format)
{
	char *type;

	type = "sSpdDioOuUxXcC";
	/*
	 * если спецификатор формата отсутствует, выводится только префикс
	 *
	 * если это левая буква - она выведется на следующей итерации
	 */
	if (!ft_strchr(type, **fmt))
		return;
	format->type = **fmt;
	if (**fmt == 'd' || **fmt == 'i' || **fmt == 'D')
		format->flag |= SIGNED;
	if (**fmt == 'D' || **fmt == 'S' || **fmt == 'O' || **fmt == 'U' || **fmt == 'E' ||
		**fmt == 'F' || **fmt == 'G' || **fmt == 'A' || **fmt == 'C')
		format->size |= L;
	if (**fmt == 'o' || **fmt == 'O')
		format->base = 8;
	if (**fmt == 'x' || **fmt == 'X')
		format->base = 16;
	//делать для U?
	if (**fmt == 'x' || **fmt == 'X' || **fmt == 'o' || **fmt == 'O' || **fmt == 'u')
		format->size |= U;

	//if (**fmt == 'o' || **fmt == 'U' || **fmt == 'x' || **fmt == 'X')
	//unsigned
	(*fmt)++;
}



