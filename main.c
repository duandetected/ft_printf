#include "ft_printf.h"
#include <math.h>

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

	char *format = "suka blyad: %0*.*sdd\n";
	int width = 20;
	int precision = 5;

	b = ft_printf(format, width, precision, "n");
	printf("%d\n", b);
	b = printf(format, width, precision, "n");
	printf("%d\n", b);
}

void test_decimal()
{
	int b;
	size_t n = 42;
	//"%0 .1 025.15-+zddd\n"
	//"%020.0d vvv\n" - при пресижене ноль не надо ставить нули в начало
	char *format = "%+#0*.*d vvv\n";
	int width = 20;
	int precision = 3;

	b = ft_printf(format, width, precision, n);
	printf("%d\n", b);
	//print_mem_bytes(&n, sizeof(n));

	b = printf(format, width, precision, n);
	printf("%d\n", b);
	//print_mem_bytes(&n, sizeof(n));
}

void test_pointer()
{
	int a = 55;
	int b;
	int *ptr = NULL;
	char *format = "%.0p, %.p";

	b = ft_printf(format, NULL);
	printf("|||||||||\n");
	printf("%d\n", b);
	b = printf(format, NULL);
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
	int d;
	char num1 = 0;
	char num2 = 0;
	char *format = "%2cvvv";
	int precision = 0;

	d = ft_printf(format, num1);
	printf("\n%d\n", d);

	d = printf(format, num1);
	printf("\n%d\n", d);
}

int main(void)
{
	//test_string();
	//printf("\n");
	//test_decimal();
	//printf("\n");
	test_pointer();
	//test_size();
	//printf("\n");
	//test_basic();
	//printf("\n");
	//test_42();
	//printf("\n");
	//test_char();
	return 0;
}