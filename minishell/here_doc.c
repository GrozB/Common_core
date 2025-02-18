#include "here_doc.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>

int	handle_here_doc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	size_t	total_size;
	size_t	capacity;
	char	*buffer;
	size_t	len;
	char	*temp;

	capacity = 1024;
	buffer = malloc(capacity);
	if (!buffer)
	{
		perror("malloc");
		return (-1);
	}
	buffer[0] = '\0';
	total_size = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		len = strlen(line);
		/* Expand buffer if necessary */
		while (total_size + len + 2 > capacity)
		{
			capacity *= 2;
			temp = realloc(buffer, capacity);
			if (!temp)
			{
				perror("realloc");
				free(buffer);
				free(line);
				return (-1);
			}
			buffer = temp;
		}
		/* Append the line and a newline */
		strcat(buffer, line);
		strcat(buffer, "\n");
		total_size += len + 1;
		free(line);
	}
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		free(buffer);
		return (-1);
	}
	if (write(pipe_fd[1], buffer, total_size) < 0)
	{
		perror("write");
		free(buffer);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	free(buffer);
	/* Close the write end so that the read end sees EOF */
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/*
 * fix_here_doc_tokens: scans the token array and splits any token that
 * begins with "<<", but is longer than 2 characters, into two tokens:
 * one containing "<<" and the other containing the rest.
 * The caller is responsible for freeing the returned array and its tokens.
 */
char	**fix_here_doc_tokens(char **tokens)
{
	int		i;
	int		new_count;
	char	**new_tokens;
	int		j;
	
	/* Count the new number of tokens */
	i = 0;
	new_count = 0;
	while (tokens[i])
	{
		if (strncmp(tokens[i], "<<", 2) == 0 && tokens[i][2] != '\0')
			new_count += 2;
		else
			new_count++;
		i++;
	}
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		/* If token starts with "<<", but has extra characters */
		if (strncmp(tokens[i], "<<", 2) == 0 && tokens[i][2] != '\0')
		{
			new_tokens[j] = strdup("<<");
			if (!new_tokens[j])
			{
				/* Free already allocated tokens on error */
				while (j > 0)
				{
					j--;
					free(new_tokens[j]);
				}
				free(new_tokens);
				return (NULL);
			}
			j++;
			new_tokens[j] = strdup(tokens[i] + 2);
			if (!new_tokens[j])
			{
				while (j > 0)
				{
					j--;
					free(new_tokens[j]);
				}
				free(new_tokens);
				return (NULL);
			}
			j++;
		}
		else
		{
			new_tokens[j] = strdup(tokens[i]);
			if (!new_tokens[j])
			{
				while (j > 0)
				{
					j--;
					free(new_tokens[j]);
				}
				free(new_tokens);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}
