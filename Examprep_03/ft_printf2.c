#include <stdarg.h>
#include <unistd.h>

static void ft_putstr(char *str, int *count)
{
	int	i = 0;

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		(*count)++;
	}
}

static void ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		(*count)++;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*count)++;
}

static void ft_puthex(unsigned int n, int *count)
{
	char *str = "0123456789abcdef";

	if (n >= 16)
		ft_puthex(n / 16, count);
	write(1, &str[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int	count = 0;
	int	i = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] != '\0')
			{
				if (format[i] == 's')
					ft_putstr(va_arg(args, char *), &count);
				else if (format[i] == 'd')
					ft_putnbr(va_arg(args, int), &count);
				else if (format[i] == 'x')
					ft_puthex(va_arg(args, unsigned int), &count);
				else
				{
					write(1, &format[i], 1);
					count++;
				}
			}
			else
				return (-1);
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
#include <stdio.h>
int	main(void)
{
	char *str = "abcd";
	int	i = 55;
	unsigned int j = 55555;
	printf("%d", printf("%s and %d plus %x", str, i, j));
	printf("\n");
	printf("%d", ft_printf("%s and %d plus %x", str, i, j));
	printf("\n");
}