#include "env_expansion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static char	*get_var_value(const char *var)
{
	char	*val = getenv(var);
	if (!val)
		return (strdup(""));
	return (strdup(val));
}

char	*expand_variables(const char *str)
{
	size_t	i = 0;
	size_t	res_size = 0;
	char	*result = NULL;
	char	*tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			size_t	j = i + 1;
			while (str[j] && is_var_char(str[j]))
				j++;
			char	*var_name = strndup(str + i + 1, j - i - 1);
			char	*var_value = get_var_value(var_name);
			free(var_name);
			size_t	val_len = strlen(var_value);
			tmp = malloc(res_size + val_len + 1);
			if (result)
			{
				memcpy(tmp, result, res_size);
				free(result);
			}
			memcpy(tmp + res_size, var_value, val_len);
			res_size += val_len;
			tmp[res_size] = '\0';
			free(var_value);
			result = tmp;
			i = j;
		}
		else
		{
			tmp = malloc(res_size + 2);
			if (result)
			{
				memcpy(tmp, result, res_size);
				free(result);
			}
			tmp[res_size] = str[i];
			res_size++;
			tmp[res_size] = '\0';
			result = tmp;
			i++;
		}
	}
	if (!result)
		result = strdup("");
	return (result);
}
