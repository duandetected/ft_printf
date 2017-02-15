#include "ft_printf.h"
#include <math.h>
#include <locale.h>

void test_size()
{
	size_t size = 2147483645;
	char *s = ft_strnew(size);
	for (size_t i = 0; i < size; i++)
		s[i] = 'x';
	printf("g%d%s", 5, s);
}

void test_string()
{
	int b;

	char *format = "%4.s";
	char *string = "42";

	b = ft_printf(format, string);
	printf("\n%d\n", b);
	b = printf(format, string);
	printf("\n%d\n", b);
}

void test_decimal()
{
	int b;
	size_t n = 9223372036854775807;
	//"%0 .1 025.15-+zddd\n"
	//"%020.0d vvv\n" - при пресижене ноль не надо ставить нули в начало
	//"%20.15d\n", 54321
	char *format = "%jd\n";
	int width = 20;
	int precision = 3;

	b = ft_printf(format, n);
	printf("%d\n", b);
	//print_mem_bytes(&n, sizeof(n));

	b = printf(format, n);
	printf("%d\n", b);
	//print_mem_bytes(&n, sizeof(n));
}

void test_pointer()
{
	int a = 55;
	int b;
	int *ptr = &ft_printf;
	//char *format = "%.0p, %.p";
	char *format = "%p\n";

	b = ft_printf(format, &ft_printf);
	printf("|||||||||\n");
	printf("%d\n", b);
	b = printf(format, &ft_printf);
	printf("|||||||||\n");
	printf("%d\n", b);
}

void test_basic()
{
	int d;
	char *str = NULL;
	char *format = "t%[\n";
	int precision = -6;

	d = ft_printf(format, precision, str);
	printf("%d\n", d);

	d = printf(format, precision, str);
	printf("%d\n", d);
}

void test_42()
{
	int d;
	int num1 = 0;
	int num2 = 0;
	char *format = "@moulitest: %#.o %#.0x";
	int precision = 0;

	d = ft_printf(format, num1, num2);
	printf("\n%d\n", d);

	d = printf(format, num1, num2);
	printf("\n%d\n", d);
}

void test_char()
{
	setlocale(LC_ALL, "");

	int d;
	int num1 = 0;
	char c = 'c';
	wchar_t* num2 = L"ÊÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B";
	//{%*c}
	//{%03c}
	char *format = "%S";
	int precision = 0;

	d = ft_printf(format, num2);
	printf("\n%d\n", d);

	d = printf(format, num2);
	printf("\n%d\n", d);
}

void test_wchar()
{
	int num = 8710;
	print_mem_bytes(&num, sizeof(num));

	char a, b, c;

	a = 226;
	b = 136;
	c = 134;

	char str[4] = {a, b, c, '\0'};

/*
	ft_putchar(a);
	ft_putchar(b);
	ft_putchar(c);
*/
	ft_putstr(str);

	//	11100010 10001000 10000110
	//  1110xxxx 10xxxxxx 10xxxxxx
	//	00000000 00100010 00000110
	//	14846086
}

void test_octal()
{
	int b;
	char *format = "%#o";
	size_t n = 0;
	int width = 20;
	int precision = 3;

	b = ft_printf(format, n);
	printf("\n%d\n", b);

	b = printf(format, n);
	printf("\n%d\n", b);
}


int main(void)
{
	//test_string();
	//printf("\n");
	//test_decimal();
	//printf("\n");
	//test_pointer();
	//printf("\n");
	//test_size();
	//printf("\n");
	//test_basic();
	//printf("\n");
	//test_42();
	//printf("\n");
	test_char();
	printf("\n");
	//test_octal();
	//printf("\n");
	//test_wchar();
	return 0;
}

/*
int main(void)
{
	ft_printf("\n");
	ft_printf("%%\n");
	ft_printf("%d\n", 42);
	ft_printf("%d%d\n", 42, 41);
	ft_printf("%d%d%d\n", 42, 43, 44);
	ft_printf("%ld\n", 2147483647);
	ft_printf("%lld\n", 9223372036854775807);
	ft_printf("%x\n", 505);
	ft_printf("%X\n", 505);
	ft_printf("%p\n", &ft_printf);
	ft_printf("%20.15d\n", 54321);
	ft_printf("%-10d\n", 3);
	ft_printf("% d\n", 3);
	ft_printf("%+d\n", 3);
	ft_printf("%010d\n", 1);
	ft_printf("%hhd\n", 0);
	ft_printf("%jd\n", 9223372036854775807);
	ft_printf("%zd\n", 4294967295);
	ft_printf("%\n");
	ft_printf("%U\n", 4294967295);
	ft_printf("%u\n", 4294967295);
	ft_printf("%o\n", 40);
	ft_printf("%%#08x\n", 42);
	ft_printf("%x\n", 1000);
	ft_printf("%#X\n", 1000);
	ft_printf("%s\n", NULL);
	ft_printf("%S\n", L"ݗݜशব");
	ft_printf("%s%s\n", "test", "test");
	ft_printf("%s%s%s\n", "test", "test", "test");
	ft_printf("%C\n", 15000);
	return (0);
}
*/