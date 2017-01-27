//
// Created by warto on 1/11/2017.
//

#ifndef FT_PRINTF_FT_PRINTF_H
#define FT_PRINTF_FT_PRINTF_H

#include <stdio.h>
#include "libft/libft.h"
#include <stdlib.h>
/*
 * to use functions with multiple parametres
 */
#include <stdarg.h>
/*
 * stores the limits of the types for the different platforms
 */
#include <limits.h>
/*
 * flag
 */
#define LEFT 1
#define PLUS 2
#define SPACE 4
#define HASH 8
#define ZEROPAD 16

#define SIGNED 32

/*
 * size
 *
 * играет роль порядок H и HH
 */

#define H 32 /* short */
#define HH 16 /* char */
#define L 8 /* long */
#define LL 4 /* long long */
#define J 2 /* max_t */
#define Z 1 /* size_t */

#define RESULT_UNSIGNED size_t
#define RESULT_SIGNED ssize_t
#define RESULT NULL

typedef struct 			s_format
{
	int		flag;
	/*
	 * сделать проверку где-то в коде на макс/мин инт
	 * для width и precision
	 *
	 * хранить базу( > 2 && < 16)
	 */
	int 	width;
	int 	precision;
	int		size;
	char 	type;
	int 	base;

	char	*prefix;
	size_t 	prefix_len;
	char 	*sufix;
	size_t 	sufix_len;
}						t_format;

/*
 * additional functions
 */
int			ft_printf(char *fmt, ...);
void		initialise_struct(t_format **format);
/*
 * check functions
 */
int			check_flags(char **fmt, t_format *format);
int			check_width(char **fmt, va_list ap, t_format *format);
int			check_precision(char **fmt, va_list ap, t_format *format);
int			check_size(char **fmt, t_format *format);
void		check_type(char **fmt, t_format *format);
/*
 * output functions
 */
void 		initialise_array(void (*foo[])(t_format* , va_list));
size_t		do_print(t_format *format, va_list ap);
void		write_string(t_format *format, va_list ap);
void		write_decimal(t_format *format, va_list ap);
void write_pointer(t_format *format, va_list ap);
/*
 * output decimal functions
 */
void 	write_d_hh(t_format *format, va_list ap);
void 	write_d_h(t_format *format, va_list ap);
void	write_d_long(t_format *format, va_list ap);

void	write_num(t_format *format, va_list ap);

#endif //FT_PRINTF_FT_PRINTF_H
