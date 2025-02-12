#include "minishell.h"
#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	count_pipes(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static t_command	**split_commands(char **tokens, int *num_commands)
{
	int			count;
	t_command	**cmds;
	int			i;
	int			start;
	int			cmd_index;
	int			j;
	int			len;
	char		**segment;

	count = count_pipes(tokens) + 1;
	cmds = malloc(sizeof(t_command *) * (count + 1));
	i = 0;
	start = 0;
	cmd_index = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0')
		{
			len = i - start;
			segment = malloc(sizeof(char *) * (len + 1));
			j = 0;
			while (j < len)
			{
				segment[j] = strdup(tokens[start + j]);
				j++;
			}
			segment[len] = NULL;
			cmds[cmd_index] = parse_command(segment);
			j = 0;
			while (j < len)
			{
				free(segment[j]);
				j++;
			}
			free(segment);
			cmd_index++;
			i++;
			start = i;
		}
		else
			i++;
	}
	if (i - start > 0)
	{
		len = i - start;
		segment = malloc(sizeof(char *) * (len + 1));
		j = 0;
		while (j < len)
		{
			segment[j] = strdup(tokens[start + j]);
			j++;
		}
		segment[len] = NULL;
		cmds[cmd_index] = parse_command(segment);
		j = 0;
		while (j < len)
		{
			free(segment[j]);
			j++;
		}
		free(segment);
		cmd_index++;
	}
	cmds[cmd_index] = NULL;
	*num_commands = cmd_index;
	return (cmds);
}

int	main(void)
{
	struct sigaction	sa;
	char				*line;
	char				**tokens;
	t_command			*cmd;
	t_command			**cmds;
	int					status;
	int					i;
	int					num_commands;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("\n");
			break;
		}
		if (*line)
			add_history(line);
		tokens = parse_input(line);
		free(line);
		if (!tokens)
		{
			fprintf(stderr, "Error parsing input\n");
			continue;
		}
		if (count_pipes(tokens) > 0)
		{
			cmds = split_commands(tokens, &num_commands);
			status = execute_pipeline(cmds, num_commands);
			free_commands(cmds, num_commands);
		}
		else
		{
			cmd = parse_command(tokens);
			status = execute_command(cmd);
			free_command(cmd);
		}
		(void)status;
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
	return (0);
}
