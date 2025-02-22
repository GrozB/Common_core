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

static int parse_dq(const char *input, int *i, char *buf, int *pos, int last_exit_status)
{
    (*i)++;
    while (input[*i] && input[*i] != '\"')
    {
        if (input[*i] == '$')
        {
            (*i)++;
            if (input[*i] == '?')
            {
                char *num = ft_itoa(last_exit_status);
                if (!num)
                    return (-1);
                int k = 0;
                while (num[k])
                {
                    buf[(*pos)++] = num[k];
                    k++;
                }
                free(num);
                (*i)++;
            }
            else
            {
                if (append_var(input, i, buf, pos) < 0)
                    return (-1);
            }
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

static int handle_quote(const char *input, int *i, char *buf, int *pos, int last_exit_status)
{
    if (input[*i] == '\"')
    {
        if (parse_dq(input, i, buf, pos, last_exit_status) < 0)
            return (-1);
    }
    else if (input[*i] == '\'')
    {
        if (parse_sq(input, i, buf, pos) < 0)
            return (-1);
    }
    return (0);
}

static char *token_builder(const char *input, int *i, int last_exit_status)
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
		if (input[*i] == '>' || input[*i] == '<')
		{
			if (pos > 0)
				break;
			buf[pos++] = input[*i];
			if (input[*i + 1] == input[*i])
			{
				(*i)++;
				buf[pos++] = input[*i];
			}
			(*i)++;
			break;
		}
		else if (input[*i] == '|')
		{
			if (pos > 0)
				break;
			buf[pos++] = input[*i];
			(*i)++;
			break;
		}
		else if (input[*i] == '$')
		{
			if (input[*i + 1] == '?')
			{
				char *num = ft_itoa(last_exit_status);
				if (!num)
				{
					free(buf);
					return (NULL);
				}
				int k = 0;
				while (num[k])
				{
					buf[pos++] = num[k];
					k++;
				}
				free(num);
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
			if (handle_quote(input, i, buf, &pos, last_exit_status) < 0)
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

static char	*parse_token(const char *input, int *i, int last_exit_status)
{
	return token_builder(input, i, last_exit_status);
}

static int	count_tokens(const char *input, int last_exit_status)
{
	int	i;
	int	count;
	char	*token;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break;
		token = token_builder(input, &i, last_exit_status);
		if (!token)
			return (-1);
		count++;
		free(token);
	}
	return (count);
}


#include <unistd.h>

char	**parse_input(const char *input, int last_exit_status)
{
	int		token_count;
	char	**tokens;
	int		i;
	int		t;
	char	*tok;
	char	**fixed_tokens;
	(void)last_exit_status;

	token_count = count_tokens(input, last_exit_status);
	if (token_count < 0)
	{
		write(2, "minishell: syntax error: unmatched quote\n", 41);
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	t = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	while (input[i])
	{
		tok = parse_token(input, &i, last_exit_status);
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
	fixed_tokens = fix_here_doc_tokens(tokens);
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (fixed_tokens);
}
