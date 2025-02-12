#include "minishell.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;

static size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strdup(const char *s)
{
	size_t	len = ft_strlen(s);
	char	*dup = malloc(len + 1);
	size_t	i;

	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	char	*joined;
	size_t	i;

	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		joined[len1 + i] = s2[i];
		i++;
	}
	joined[len1 + len2] = '\0';
	return (joined);
}

static char	*find_command_path(const char *cmd)
{
	char			*path_env;
	char			*path_copy;
	char			*p;
	size_t			dir_len;
	char			*dir;
	char			*tmp;
	char			*full_path;
	struct stat		st;

	if (strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (ft_strdup(cmd));
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	p = path_copy;
	while (*p)
	{
		char *colon = strchr(p, ':');
		if (colon)
			dir_len = colon - p;
		else
			dir_len = ft_strlen(p);
		dir = malloc(dir_len + 1);
		if (!dir)
			break;
		memcpy(dir, p, dir_len);
		dir[dir_len] = '\0';
		tmp = ft_strjoin(dir, "/");
		free(dir);
		if (!tmp)
			break;
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			break;
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		if (!colon)
			break;
		p = colon + 1;
	}
	free(path_copy);
	return (ft_strdup(cmd));
}

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

static int	execute_builtin(t_command *cmd)
{
	if (strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit());
	if (strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args));
	if (strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	if (strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (strcmp(cmd->args[0], "env") == 0)
		return (builtin_env());
	return (1);
}

int	execute_command(t_command *cmd)
{
	pid_t	pid;
	int		status;
	int		fd_in;
	int		fd_out;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (cmd->infile)
		{
			fd_in = open(cmd->infile, O_RDONLY);
			if (fd_in < 0)
			{
				perror("open infile");
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (cmd->outfile)
		{
			if (cmd->append)
				fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0)
			{
				perror("open outfile");
				exit(1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		{
			char	*cmd_path = find_command_path(cmd->args[0]);
			if (!cmd_path)
				exit(1);
			if (execve(cmd_path, cmd->args, environ) < 0)
			{
				perror("execve");
				free(cmd_path);
				exit(1);
			}
			free(cmd_path);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		/* Only print an extra newline if "cat" succeeded */
		if (cmd->args && cmd->args[0] && strcmp(cmd->args[0], "cat") == 0)
		{
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				printf("\n");
		}
	}
	return (status);
}
