#include "minishell.h"
#include "here_doc.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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
	if (strcmp(token, "<<") == 0)
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
	cmd->here_doc_fd = -1;
	arg_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redirection(tokens[i]))
		{
			i++;
			if (!tokens[i])
			{
				fprintf(stderr, "minishell: syntax error: missing redirection target\n");
				free(cmd);
				return (NULL);
			}
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
			else
			{
				fprintf(stderr, "minishell: syntax error: missing redirection target\n");
				free_command(cmd);
				return (NULL);
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
			else
			{
				fprintf(stderr, "minishell: syntax error: missing redirection target\n");
				free_command(cmd);
				return (NULL);
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
			else
			{
				fprintf(stderr, "minishell: syntax error: missing redirection target\n");
				free_command(cmd);
				return (NULL);
			}
		}
		else if (strcmp(tokens[i], "<<") == 0)
		{
			i++;
			if (tokens[i])
			{
				cmd->here_doc_fd = handle_here_doc(tokens[i]);
				i++;
			}
			else
			{
				fprintf(stderr, "minishell: syntax error: missing here-doc delimiter\n");
				free_command(cmd);
				return (NULL);
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
	if (cmd->here_doc_fd != -1)
		close(cmd->here_doc_fd);
	free(cmd);
}
