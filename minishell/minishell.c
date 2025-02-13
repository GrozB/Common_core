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
	int count = 0, i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	check_trailing_pipe(char **tokens)
{
	int i = 0;
	while (tokens[i])
		i++;
	if (i > 0 && tokens[i - 1][0] == '|' && tokens[i - 1][1] == '\0')
	{
		fprintf(stderr, "minishell: syntax error: empty command\n");
		return (-1);
	}
	return (0);
}

static int	check_pipe_token(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		if (strchr(tokens[i], '|'))
		{
			if (tokens[i][0] != '|' || tokens[i][1] != '\0')
			{
				fprintf(stderr,
					"minishell: syntax error: invalid pipe token\n");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static char	**build_segment(char **tokens, int start, int len)
{
	int j = 0;
	char **seg = malloc(sizeof(char *) * (len + 1));
	if (!seg)
		return (NULL);
	while (j < len)
	{
		seg[j] = strdup(tokens[start + j]);
		if (!seg[j])
		{
			while (j > 0)
			{
				j--;
				free(seg[j]);
			}
			free(seg);
			return (NULL);
		}
		j++;
	}
	seg[len] = NULL;
	return (seg);
}

static void	free_segment(char **seg)
{
	int j = 0;
	while (seg[j])
	{
		free(seg[j]);
		j++;
	}
	free(seg);
}

static int	next_pipe(char **tokens, int start)
{
	int i = start;
	while (tokens[i] && !(tokens[i][0] == '|' && tokens[i][1] == '\0'))
		i++;
	return (i);
}

static t_command	*process_segment(char **tokens, int start, int end)
{
	int len = end - start;
	char **seg;
	t_command *cmd;
	if (len <= 0)
	{
		fprintf(stderr, "minishell: syntax error: empty command\n");
		return (NULL);
	}
	seg = build_segment(tokens, start, len);
	if (!seg)
		return (NULL);
	cmd = parse_command(seg);
	free_segment(seg);
	return (cmd);
}

static t_command	**split_commands(char **tokens, int *num_commands)
{
	int count, i, start, cmd_index, end;
	t_command **cmds;
	if (check_pipe_token(tokens) < 0)
		return (NULL);
	if (check_trailing_pipe(tokens) < 0)
		return (NULL);
	count = count_pipes(tokens) + 1;
	cmds = malloc(sizeof(t_command *) * (count + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	cmd_index = 0;
	while (tokens[i])
	{
		start = i;
		end = next_pipe(tokens, start);
		cmds[cmd_index] = process_segment(tokens, start, end);
		if (!cmds[cmd_index])
		{
			free(cmds);
			return (NULL);
		}
		cmd_index++;
		if (tokens[end])
			i = end + 1;
		else
			i = end;
	}
	cmds[cmd_index] = NULL;
	*num_commands = cmd_index;
	return (cmds);
}

static void	process_line(char **tokens)
{
	int status, i, num_commands;
	t_command *cmd;
	t_command **cmds;
	if (check_pipe_token(tokens) < 0)
	{
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		return;
	}
	if (count_pipes(tokens) > 0)
	{
		cmds = split_commands(tokens, &num_commands);
		if (!cmds)
		{
			i = 0;
			while (tokens[i])
			{
				free(tokens[i]);
				i++;
			}
			free(tokens);
			return;
		}
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

int	main(void)
{
	struct sigaction sa;
	char *line;
	char **tokens;
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
			continue;
		process_line(tokens);
	}
	return (0);
}
