#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

int	builtin_pwd(void)
{
	char	buf[1024];

	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}

int	builtin_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

int	builtin_cd(char **args)
{
	if (!args[1])
	{
		fprintf(stderr, "cd: missing argument\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_exit(void)
{
	exit(0);
	return (0);
}
