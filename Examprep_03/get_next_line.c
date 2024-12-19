#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	int	i;
	char *dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if(!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
	
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read = 0;
	static int	buffer_pos = 0;
	char		line[70000];
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read < 0)
				return (NULL);
			if (buffer_read == 0)
				break ;
		}
		if (buffer_pos < buffer_read)
		{
			line[i++] = buffer[buffer_pos];
			if (buffer[buffer_pos++] == '\n')
				break ;
		}
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	main(void)
{
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open("txt.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line1 = get_next_line(fd);
	line2 = get_next_line(fd);
	line3 = get_next_line(fd);
	char *line4 = get_next_line(fd); // Попытка прочитать за пределами файла
	if (line1)
	{
		printf("Line 1: %s", line1); // Ожидается "Hello\n"
		free(line1);
	}
	if (line2)
	{
		printf("Line 2: %s", line2); // Ожидается "World\n"
		free(line2);
	}
	if (line3)
	{
		printf("Line 3: %s", line3); // Ожидается "42\n"
		free(line3);
	}
	if (line4)
	{
		printf("Line 4: %s", line4); // Должно быть NULL,
		free(line4);
	}
	close(fd);
	return (0);
}
