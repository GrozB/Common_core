/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:06:31 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/14 18:54:36 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_EXPANSION_H
# define ENV_EXPANSION_H
# include "../minishell.h"

// Argument_allocation.c
int			expand_args_capacity(t_command *cmd, int *args_capacity);
int			add_argument(t_command *cmd,
				char *arg, int *args_count, int *args_capacity);
int			handle_split_words(t_command *cmd,
				char **words, int *args_count, int *args_capacity);
int			handle_argument(t_command *cmd,
				char *token, int *args_count, int *args_capacity);
int			allocate_final_arguments(t_command *cmd, int args_count);

// Argument_finalize.c
int			handle_empty_arguments(t_command *cmd);
int			finalize_arguments(t_command *cmd, int args_count);
int			process_tokens_env(t_command *cmd,
				char ***tokens, int *env, t_shell *shell);

// command_parser.c
t_command	*parse_command(char **tokens, int last_exit_status, t_shell *shell);
void		free_command_resources(t_command *cmd);
void		free_command(t_command *cmd);

// filename_utils.c
char		*get_filename_from_words(char *token);
char		*get_filename(char *op, char *token);

// heredoc_redir.c
int			handle_heredoc_redir(t_command *cmd,
				char *filename, int last_exit_status, t_shell *shell);
int			handle_redir_type(t_command *cmd, char **redir, t_shell *shell);
int			handle_redirection(t_command *cmd,
				char ***tokens, int last_exit_status, t_shell *shell);

// itoa_utils.c
int			count_len(long num);
char		*ft_itoa(int n);

//quote_noexpand.c
int			handle_quote_noexpand(const char *input, int *i, t_buf_info *bi);
int			parse_dq_noexpand(const char *input, int *i, t_buf_info *bi);
int			parse_sq_noexpand(const char *input, int *i, t_buf_info *bi);

// redirection_utils.c
int			is_redirection(const char *token);
int			add_redir(t_command *cmd, t_redir_type type, const char *filename);
char		*remove_quotes(const char *s);

// string_utils.c
void		free_str_array(char **arr);
int			ft_strncpy(char *dest, const char *src, size_t n);

// syntax_checker1.c
int			check_pipe_syntax(char **tokens);
int			check_unexpected_newline(char **tokens, int i);
int			check_redirection_syntax_error(char **tokens, int i);
int			check_redirection_syntax(char **tokens, int i);
int			check_trailing_pipe_or_redir(char **tokens, int i);

// syntax_checker2.c
int			check_pipe_and_redir_syntax(char **tokens, int i);
int			check_syntax_errors(char **tokens);

// tb_token1.c
int			tb_append(t_tb *tb, char c);
int			tb_process_special(t_tb *tb);
int			tb_process_dollar(t_tb *tb);
int			tb_process_quote(t_tb *tb);
int			tb_process_else(t_tb *tb);

// tb_token2.c
int			tb_handle_current_char(t_tb *tb);
int			tb_loop(t_tb *tb);
char		*tb_finalize(t_tb *tb);
char		*token_builder_noexpand(const char *input, int *i);

// token_collection1.c
int			skip_ws(const char *input, int i);
char		**allocate_tokens(int token_count);
int			handle_token_error(char **tokens, int t);
int			collect_tokens(const char *input,
				int last_exit_status, char **tokens, t_shell *shell);

// token_collection2.c
char		**collect_tokens_loop(const char *input,
				int last_exit_status, int token_count, t_shell *shell);
char		**handle_token_fixing(char **tokens);
char		**collect_and_fix_tokens(const char *input,
				int last_exit_status, int token_count, t_shell *shell);
char		**parse_input(const char *input,
				int last_exit_status, t_shell *shell);

// token_counter.c
int			count_tokens(const char *input,
				int last_exit_status, t_shell *shell);

// word_split_utils.c
int			count_words(const char *str);
char		*allocate_word(const char *str, int start, int len);
char		**free_words(char **words, int count);
char		**split_words(const char *str, int word_count);
char		**word_split(const char *str);

#endif
