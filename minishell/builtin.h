#ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_echo(char **args);
int	builtin_pwd(void);
int	builtin_env(void);
int	builtin_cd(char **args);
int	builtin_exit(void);

#endif
