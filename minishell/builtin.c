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

int	builtin_export(char **args)
{
	int		i;
	int		key_len;
	char	*eq;
	char	*key;
	char	**new_env;
	int		count;

	if (!args[1])
	{
		i = 0;
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (0);
	}
	eq = strchr(args[1], '=');
	if (!eq)
	{
		fprintf(stderr, "export: invalid argument: %s\n", args[1]);
		return (1);
	}
	key_len = eq - args[1];
	key = strndup(args[1], key_len);
	if (!key)
		return (1);
	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], key, key_len) == 0 && environ[i][key_len] == '=')
		{
			free(environ[i]);
			environ[i] = strdup(args[1]);
			free(key);
			return (0);
		}
		i++;
	}
	free(key);
	count = 0;
	while (environ[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = strdup(args[1]);
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}

int	builtin_unset(char **args)
{
	int	i;
	int	key_len;

	if (!args[1])
	{
		fprintf(stderr, "unset: not enough arguments\n");
		return (1);
	}
	key_len = strlen(args[1]);
	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], args[1], key_len) == 0 &&
				environ[i][key_len] == '=')
		{
			free(environ[i]);
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	builtin_exit(char **args)
{
	int	argc = 0;
	int	i;
	int	neg;
	long long num;
	int	exit_code;
	char	*err_msg;

	while (args[argc])
		argc++;
	if (argc > 2)
	{
		err_msg = "exit: too many arguments\n";
		write(2, err_msg, 27);
		return (1);
	}
	if (argc == 1)
		exit(0);
	i = 0;
	neg = 0;
	if (args[1][0] == '-' || args[1][0] == '+')
	{
		if (args[1][0] == '-')
			neg = 1;
		i++;
	}
	if (!args[1][i])
	{
		err_msg = "exit: numeric argument required\n";
		write(2, err_msg, 34);
		exit(2);
	}
	num = 0;
	while (args[1][i])
	{
		if (!is_digit(args[1][i]))
		{
			err_msg = "exit: numeric argument required\n";
			write(2, err_msg, 34);
			exit(2);
		}
		num = num * 10 + (args[1][i] - '0');
		i++;
	}
	if (neg)
		num = -num;
	exit_code = (int)(num % 256);
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}
