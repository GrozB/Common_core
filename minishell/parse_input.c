#include "minishell.h"
#include "env_expansion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

static int	append_var(const char *input, int *i, char *buf, int *pos)
{
	int		start;
	char	*tmp;
	char	*val;
	int		j;

	start = *i;
	while (input[*i] && is_var_char(input[*i]))
		(*i)++;
	tmp = strndup(input + start, *i - start);
	if (!tmp)
		return (-1);
	val = getenv(tmp);
	free(tmp);
	if (!val)
		val = "";
	j = 0;
	while (val[j])
	{
		buf[(*pos)++] = val[j];
		j++;
	}
	return (0);
}

static int	parse_dq(const char *input, int *i, char *buf, int *pos)
{
	(*i)++;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')
		{
			(*i)++;
			if (append_var(input, i, buf, pos) < 0)
				return (-1);
		}
		else
		{
			buf[(*pos)++] = input[*i];
			(*i)++;
		}
	}
	if (input[*i] != '\"')
	{
		fprintf(stderr, "minishell: syntax error: unmatched \"\n");
		return (-1);
	}
	(*i)++;
	return (0);
}

static int	parse_sq(const char *input, int *i, char *buf, int *pos)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		buf[(*pos)++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '\'')
	{
		fprintf(stderr, "minishell: syntax error: unmatched '\n");
		return (-1);
	}
	(*i)++;
	return (0);
}

static int	handle_quote(const char *input, int *i, char *buf, int *pos)
{
	if (input[*i] == '\"')
	{
		if (parse_dq(input, i, buf, pos) < 0)
			return (-1);
	}
	else if (input[*i] == '\'')
	{
		if (parse_sq(input, i, buf, pos) < 0)
			return (-1);
	}
	return (0);
}

static char	*token_builder(const char *input, int *i)
{
	int		pos;
	int		len;
	char	*buf;

	pos = 0;
	len = strlen(input);
	buf = malloc(len + 1);
	if (!buf)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i]))
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			if (handle_quote(input, i, buf, &pos) < 0)
			{
				free(buf);
				return (NULL);
			}
		}
		else if (input[*i] == '$')
		{
			(*i)++;
			if (append_var(input, i, buf, &pos) < 0)
			{
				free(buf);
				return (NULL);
			}
		}
		else
		{
			buf[pos++] = input[*i];
			(*i)++;
		}
	}
	buf[pos] = '\0';
	return (buf);
}

static char	*parse_token(const char *input, int *i)
{
	return (token_builder(input, i));
}

static int	count_tokens(const char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (input[i])
		{
			count++;
			while (input[i] && !is_whitespace(input[i]))
			{
				if (input[i] == '\"' || input[i] == '\'')
				{
					char quote = input[i];
					i++;
					while (input[i] && input[i] != quote)
						i++;
					if (input[i] == quote)
						i++;
				}
				else
					i++;
			}
		}
	}
	return (count);
}

char	**parse_input(const char *input)
{
	int		token_count;
	char	**tokens;
	int		i;
	int		t;
	char	*tok;

	token_count = count_tokens(input);
	if (token_count < 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	t = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	while (input[i])
	{
		tok = parse_token(input, &i);
		if (!tok)
		{
			while (t > 0)
			{
				t--;
				free(tokens[t]);
			}
			free(tokens);
			return (NULL);
		}
		tokens[t++] = tok;
		while (input[i] && is_whitespace(input[i]))
			i++;
	}
	tokens[t] = NULL;
	return (tokens);
}
