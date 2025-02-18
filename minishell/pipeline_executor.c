#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
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

void	free_commands(t_command **cmds, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		free_command(cmds[i]);
		i++;
	}
	free(cmds);
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

#include <sys/types.h>
#include <sys/wait.h>

int	execute_pipeline(t_command **cmds, int n)
{
	int		i;
	int		status;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;
	int		final_status;
	int		raw_status;

	prev_fd = -1;
	i = 0;
	while (i < n)
	{
		if (i < n - 1)
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe");
				return (1);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < n - 1)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			/* Here-document redirection takes precedence over infile redirection */
			if (cmds[i]->here_doc_fd != -1)
			{
				dup2(cmds[i]->here_doc_fd, STDIN_FILENO);
				close(cmds[i]->here_doc_fd);
			}
			else if (cmds[i]->infile)
			{
				int fd_in = open(cmds[i]->infile, O_RDONLY);
				if (fd_in < 0)
				{
					perror("open infile");
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (cmds[i]->outfile)
			{
				int fd_out;
				if (cmds[i]->append)
					fd_out = open(cmds[i]->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd_out = open(cmds[i]->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out < 0)
				{
					perror("open outfile");
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			{
				char *cmd_path = find_command_path(cmds[i]->args[0]);
				if (!cmd_path)
					exit(1);
				if (execve(cmd_path, cmds[i]->args, environ) < 0)
				{
					perror("execve");
					free(cmd_path);
					exit(1);
				}
				free(cmd_path);
			}
		}
		/* Parent process: close parent's copy of here_doc_fd, if set */
		if (cmds[i]->here_doc_fd != -1)
			close(cmds[i]->here_doc_fd);

		if (prev_fd != -1)
			close(prev_fd);
		if (i < n - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	final_status = 0;
	i = 0;
	while (i < n)
	{
		raw_status = 0;
		wait(&raw_status);
		/* If the process terminated normally, extract exit code from upper 8 bits */
		if ((raw_status & 0x7F) == 0)
			status = (raw_status >> 8) & 0xFF;
		else
			status = 128 + (raw_status & 0x7F);
		if (status != 0)
			final_status = status;
		i++;
	}
	return (final_status);
}
