/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:48:25 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/16 15:19:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

void	apply_redirections(t_command *cmd, t_plchild_data *d, t_shell *shell);
void	free_commands(t_command **cmds, int num_commands);
void	close_heredoc_fds(t_command *cmd);
void	close_heredoc_fds_pipeline(t_command *cmd);

int		single_redir(t_redir *redir, int saved_in, int saved_out);

int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_plchild_data *d, t_shell *shell);
int		exec_builtin_command(t_command *cmd, t_shell *shell, t_plchild_data *d);
int		handle_builtin_redirection(t_command *cmd,
			int *saved_in, int *saved_out);

void	handle_cmd_not_found(t_command *cmd, t_plchild_data *d);
void	handle_external_no_path(t_command *cmd,
			t_plchild_data *d, t_shell *shell);

void	sigint_print_handler(int sig);
void	handle_external_path(t_command *cmd,
			char *cmd_path, t_plchild_data *d, t_shell *shell);
void	handle_external_command(t_pipeline_child *pc,
			t_plchild_data *d, t_shell *shell);

int		env_count(char **env);
char	*create_env_entry_v1(const char *cmd_path);
char	**allocate_env_array(int size);
int		copy_env_entry(char **res, char *env_entry, int j);
char	**build_envp(t_shell *shell, const char *cmd_path);

char	**copy_env_with_cmd_path(t_shell *shell,
			const char *cmd_path, int size, int *found);
char	**add_cmd_path_to_env(char **res, const char *cmd_path);

int		execute_command(t_command *cmd, t_shell *shell, t_plchild_data *d);

char	*format_token(const char *token);

char	*search_in_path_loop(char *p, const char *cmd);

char	*search_in_path(const char *path_env, const char *cmd);
char	*find_command_path(t_shell *shell, const char *cmd);
void	check_if_directory(t_command *cmd, char *cmd_path);
void	print_error_message(const char *cmd_name);
int		get_exit_code_by_errno(void);

int		execute_pipeline(t_command **cmds, int n, t_shell *shell);
int		launch_pipeline_child(t_plchild_data *d, t_shell *shell);
int		init_pipeline_children(pid_t **pids, int n, int *prev_fd);

void	pipeline_child_proc(t_pipeline_child *pc,
			t_plchild_data *d, t_shell *shell);
int		open_in_redir_file(t_redir *redir,
			t_command *cmd, t_plchild_data *d, t_shell *shell);

void	handle_in_redir(t_redir *redir, t_command *cmd,
			t_plchild_data *d, t_shell *shell);
void	handle_out_redir(const char *filename);
void	handle_append_redir(const char *filename);
void	handle_heredoc_redirect(int here_doc_fd);

size_t	ft_strlen(const char *s);
void	err_msg(const char *prefix, const char *message);
char	*ft_strdup(const char *s);

void	wait_for_external_command(pid_t pid, int *status);
void	handle_external_command_signals(void);

#endif
