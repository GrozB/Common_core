#ifndef ENV_EXPANSION_H
# define ENV_EXPANSION_H

char *expand_variables(const char *str, int last_exit_status);
char	*process_token(const char *token, int last_exit_status);

#endif
