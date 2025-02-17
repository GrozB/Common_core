#include "env_expansion.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
	    (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static char	*ft_itoa(int n)
{
	int		temp;
	int		len;
	int		neg;
	char	*str;

	if (n == 0)
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	temp = n;
	len = 0;
	while (temp)
	{
		len++;
		temp /= 10;
	}
	len += neg;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

char	*expand_variables(const char *str, int last_exit_status)
{
	int		i = 0;
	int		pos = 0;
	int		len = strlen(str);
	char	*res = malloc(len * 2 + 1);
	char	*temp;
	int		j;
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				temp = ft_itoa(last_exit_status);
				if (!temp)
				{
					free(res);
					return (NULL);
				}
				j = 0;
				while (temp[j])
				{
					res[pos] = temp[j];
					pos++;
					j++;
				}
				free(temp);
				i++;
			}
			else
			{
				int	start = i;
				while (str[i] && is_var_char(str[i]))
					i++;
				temp = strndup(str + start, i - start);
				if (!temp)
				{
					free(res);
					return (NULL);
				}
				{
					char *val = getenv(temp);
					j = 0;
					free(temp);
					if (!val)
						val = "";
					while (val[j])
					{
						res[pos] = val[j];
						pos++;
						j++;
					}
				}
			}
		}
		else
		{
			res[pos] = str[i];
			pos++;
			i++;
		}
	}
	res[pos] = '\0';
	return (res);
}
