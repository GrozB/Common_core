/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:43:31 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/14 18:54:03 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include "../minishell.h"

//command_array.c
t_command	**allocate_command_array(int count);
void		free_command_array(t_command **cmds, int cmd_index);

//command_processing.c
t_command	*process_segment(char **tokens, int *p, t_shell *shell);
t_command	*process_command_segment(char **tokens, int *seg, t_shell *shell);
int			process_commands(char **tokens,
				t_command **cmds, int *info, t_shell *shell);
t_command	**split_commands(char **tokens, int *num_commands,
				int last_exit_status, t_shell *shell);

//env.c
int			count_env(char **envp);
char		**copy_envp(char **envp);
void		initialize_shell(t_shell *shell, char **envp);

//execution.c
int			handle_pipeline_execution(char **tokens, t_shell *shell);
int			handle_single_command_execution(char **tokens,
				t_shell *shell, t_plchild_data *d);
int			process_line(char **tokens, t_shell *shell, t_plchild_data *d);
void		process_tokens(char **tokens, t_shell *shell, t_plchild_data *d);
void		process_input_line(char *line, t_shell *shell, t_plchild_data *d);

//heredoc_exec.c
void		heredoc_sigint_handler(int sig);
int			process_heredoc_line_input(int *fd_line, char *line,
				t_heredoc_info *info, t_shell *shell);
int			process_heredoc_input(int pipe_fd,
				t_heredoc_info *info, int *line_number, t_shell *shell);

//heredoc_utils.c
void		convert_line_number_to_str(int line_number, char *line_number_str);
void		build_heredoc_warning_message(char *warning_msg,
				int *line_number, t_heredoc_info *info);
int			handle_heredoc_warning(int *line_number, t_heredoc_info *info);

//main.c
int			main(int argc, char **argv, char **envp);
size_t		ft_strcpy(char *dst, const char *src);

//pipe_errors.c
int			handle_pipe_redirection_errors(char **tokens, t_shell *shell);
int			handle_syntax_and_redir_errors(char **tokens, t_shell *shell);

//redir_errors.c
int			check_redir_pair(char *current, char *next);
int			check_consecutive_redirs(char **tokens);
int			handle_empty_tokens(char **tokens);
int			handle_syntax_errors(char **tokens, t_shell *shell);
int			handle_redirection_errors(char **tokens, t_shell *shell);

//segment.c
char		**build_segment(char **tokens, int start, int len);
void		free_segment(char **seg);
int			next_pipe(char **tokens, int start);
int			validate_split_conditions(char **tokens, int *num_commands);

//signal.c
void		sigint_handler(int sig);
void		setup_signal_handlers(void);
void		handle_interruption(t_shell *shell);
void		close_inherited_fds(void);

//token_utils.c
int			count_pipes(char **tokens);
int			check_trailing_pipe(char **tokens);
int			validate_pipe_token(char *token);
int			check_pipe_token(char **tokens);
int			remove_empty_tokens(char **tokens);

#endif
