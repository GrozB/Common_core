#include "minishell.h"
#include <stdlib.h>
#include <string.h>

static int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (strcmp(token, ">") == 0)
		return (1);
	if (strcmp(token, ">>") == 0)
		return (1);
	if (strcmp(token, "<") == 0)
		return (1);
	return (0);
}

t_command	*parse_command(char **tokens)
{
	t_command	*cmd;
	int			i;
	int			arg_count;
	int			j;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	arg_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redirection(tokens[i]))
		{
			i++;
			if (tokens[i])
				i++;
		}
		else
		{
			arg_count++;
			i++;
		}
	}
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], ">") == 0)
		{
			i++;
			if (tokens[i])
			{
				cmd->outfile = strdup(tokens[i]);
				cmd->append = 0;
				i++;
			}
		}
		else if (strcmp(tokens[i], ">>") == 0)
		{
			i++;
			if (tokens[i])
			{
				cmd->outfile = strdup(tokens[i]);
				cmd->append = 1;
				i++;
			}
		}
		else if (strcmp(tokens[i], "<") == 0)
		{
			i++;
			if (tokens[i])
			{
				cmd->infile = strdup(tokens[i]);
				i++;
			}
		}
		else
		{
			cmd->args[j] = strdup(tokens[i]);
			j++;
			i++;
		}
	}
	cmd->args[j] = NULL;
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}
