/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:45:55 by bgroz             #+#    #+#             */
/*   Updated: 2024/05/13 15:27:45 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_freeing(char **mem)
{
	if (*mem != NULL)
	{
		free (*mem);
		*mem = NULL;
	}
}

static char	*extract_line(char **remainder)
{
	char	*newline;
	char	*line;
	char	*new_remainder;
	char	temp;

	line = NULL;
	newline = ft_strchr(*remainder, '\n');
	if (newline != NULL && *(newline + 1) != '\0')
	{
		temp = *(newline + 1);
		*(newline + 1) = '\0';
		line = ft_strdup(*remainder);
		*(newline + 1) = temp;
		new_remainder = ft_strdup(newline + 1);
		ft_freeing (remainder);
		*remainder = new_remainder;
	}
	else
	{
		line = ft_strdup(*remainder);
		ft_freeing(remainder);
	}
	return (line);
}

static int	append_to_remainder(int fd, char **remainder, char *mem)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = read(fd, mem, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		mem[bytes_read] = '\0';
		temp = ft_strjoin(*remainder, mem);
		ft_freeing (remainder);
		*remainder = temp;
		if (ft_strchr(mem, '\n'))
			break ;
		bytes_read = read(fd, mem, BUFFER_SIZE);
	}
	return (bytes_read);
}

static int	read_data(int fd, char **remainder)
{
	char	*mem;
	ssize_t	bytes_read;

	mem = (char *)malloc(BUFFER_SIZE + 1);
	if (!mem)
	{
		ft_freeing (remainder);
		return (-1);
	}
	bytes_read = append_to_remainder(fd, remainder, mem);
	free (mem);
	if (bytes_read < 0)
		ft_freeing(remainder);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = read_data(fd, &remainder);
	if ((bytes_read == -1) || (bytes_read == 0 && (remainder == NULL
				|| *remainder == '\0')))
	{
		ft_freeing (&remainder);
		return (NULL);
	}
	line = extract_line(&remainder);
	if (line == NULL && remainder != NULL && *remainder != '\0')
	{
		line = ft_strdup(remainder);
		ft_freeing (&remainder);
	}
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("[%s]\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	printf("[%s]\n", line);
// 	close(fd);
// }
