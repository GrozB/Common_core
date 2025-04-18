/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:23:08 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:53:18 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../minishell.h"

char	*process_delimiter(const char *delimiter,
			int last_exit_status, int *no_expand, t_shell *shell);
int		setup_signal_handler(struct sigaction *sa, struct sigaction *old_sa);
int		handle_line_input(int pipe_fd, char *line,
			char *cmp_line, int no_expand);
int		handle_dollar_question(int *i, t_buf_info *bi, int last_exit_status);
int		process_heredoc_line(char *line,
			char **cmp_line, t_heredoc_info *info, t_shell *shell);

int		handle_single_quote(const char *line, int *i, t_buf_info *bi);
int		handle_double_quote(const char *line, int *i, t_buf_info *bi);
int		handle_dollar(const char *line, int *i, t_buf_info *bi, t_shell *shell);

char	**fix_here_doc_tokens(char **tokens);

int		handle_heredoc_line(int pipe_fd, char *line,
			t_heredoc_info *info, t_shell *shell);
int		heredoc_loop(int pipe_fd, char *real_delim,
			int no_expand, t_shell *shell);
int		init_here_doc(const char *delimiter, t_heredoc_info *info,
			struct sigaction *sa, struct sigaction *old_sa);
int		create_pipe(int *pipe_fd, t_heredoc_info *info,
			struct sigaction *old_sa);
int		finalize_here_doc(int *pipe_fd, t_heredoc_info *info,
			struct sigaction *old_sa, int result);

char	*expand_vars(const char *line, int last_exit_status, t_shell *shell);

int		handle_here_doc(const char *delimiter,
			int last_exit_status, t_shell *shell);

int		exit_status(int status);
void	free_new_tokens_on_failure(char **new_tokens, int count);

#endif
