/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:08:45 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/17 19:02:16 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_env(t_shell *shell);

const char	*custom_strerror(int errnum);
int			cd_update_env(t_shell *shell, char *oldcwd, char *newcwd);

int			builtin_cd(t_shell *shell, char **args);
char		*cd_target(char **args, char *oldcwd, t_shell *shell);

int			update_existing_env(t_shell *shell,
				int index, char *new_entry, int overwrite);
int			add_new_env(t_shell *shell, char *new_entry);
int			env_len(char **envp);
void		handle_exit_error(char **args, t_plchild_data *d, t_shell *shell);
int			handle_exit_interactive(char **args,
				t_plchild_data *d, t_shell *shell, int argc);
int			handle_exit_non_interactive(char **args,
				t_plchild_data *d, t_shell *shell, int argc);

int			my_setenv(t_shell *shell,
				const char *name, const char *value, int overwrite);

long long	parse_exit_number(char *arg, int *error);
void		_error(char **args, t_plchild_data *d);

void		cleanup_exit_resources(char **args, t_plchild_data *d);

void		exit_no_args(char **args, t_plchild_data *d, t_shell *shell);
int			builtin_exit(char **args, t_plchild_data *d, t_shell *shell);
void		exit_with_args(char **args, t_plchild_data *d,
				t_shell *shell, int argc);

char		**copy_env(char **envp);
void		sort_env(char **env, int size);
void		print_export_var(char *env_entry);
int			export_set_with_value(t_shell *shell, char *arg, char *eq);

int			is_valid_identifier(const char *str);
int			builtin_export(t_shell *shell, char **args);
int			export_print(t_shell *shell);

int			add_name_no_value(t_shell *shell, const char *name);
void		remove_plain_name(t_shell *shell, const char *name);
int			handle_export_no_value(t_shell *shell, char *arg);

int			export_set_var(t_shell *shell, char *arg);
int			export_set_vars(t_shell *shell, char **args);

long long	ft_atoll(const char *str, char **endptr);

int			is_valid_unset_name(const char *str);
void		my_unsetenv(t_shell *shell, const char *name);
int			builtin_unset(t_shell *shell, char **args);
char		*cd_resolve_home(char *arg, t_shell *shell);

int			ft_isspace(int c);
void		free_envp(char **envp);
char		*my_getenv(t_shell *shell, const char *name);
int			find_env_index(t_shell *shell, const char *name, size_t name_len);
char		*create_env_entry(const char *name, const char *value);

#endif
