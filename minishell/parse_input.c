#include "minishell.h"
#include "env_expansion.h"
#include "here_doc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Returns 1 if c is a whitespace character */
static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

/* Returns 1 if c is valid in a variable name */
static int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
	    (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

/* Append a variable's value to buf; returns -1 on error */
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

/* Parse double-quoted segment; returns -1 on error */
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

/* Parse single-quoted segment; returns -1 on error */
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

/* Handle a quoted segment; returns -1 on error */
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

/* Build one token with variable expansion; returns a new token or NULL on error */
static char	*token_builder(const char *input, int *i)
{
	int		pos;
	int		buf_len;
	char	*buf;

	pos = 0;
	buf_len = strlen(input) * 2;
	buf = malloc(buf_len + 1);
	if (!buf)
		return (NULL);
	while (input[*i] && !is_whitespace(input[*i]))
	{
		if (input[*i] == '$')
		{
			/* Check if next character is '?' */
			if (input[*i + 1] == '?')
			{
				buf[pos++] = '$';
				buf[pos++] = '?';
				(*i) += 2;
			}
			else
			{
				(*i)++;
				if (append_var(input, i, buf, &pos) < 0)
				{
					free(buf);
					return (NULL);
				}
			}
		}
		else if (input[*i] == '\"' || input[*i] == '\'')
		{
			if (handle_quote(input, i, buf, &pos) < 0)
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

/* Returns one token from input */
static char	*parse_token(const char *input, int *i)
{
	return (token_builder(input, i));
}

/* Count tokens and detect unmatched quotes; returns -1 on error */
static int	count_tokens(const char *input)
{
	int	i;
	int	count;
	char	quote;

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
					quote = input[i];
					i++;
					while (input[i] && input[i] != quote)
						i++;
					if (input[i] != quote)
						return (-1);
					i++;
				}
				else
					i++;
			}
		}
	}
	return (count);
}

/* Main parsing function; returns an array of tokens or NULL on error.
   Each token is expanded for variables (including $?). */
char	**parse_input(const char *input, int last_exit_status)
{
	int		token_count;
	char	**tokens;
	int		i;
	int		t;
	char	*tok;
	char	**fixed_tokens;

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
		{
			char *expanded = expand_variables(tok, last_exit_status);
			free(tok);
			tok = expanded;
		}
		tokens[t++] = tok;
		while (input[i] && is_whitespace(input[i]))
			i++;
	}
	tokens[t] = NULL;
	/* Now fix tokens that combine the here-doc operator and delimiter */
	fixed_tokens = fix_here_doc_tokens(tokens);
	/* Free the original tokens */
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (fixed_tokens);
}
