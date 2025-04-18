/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:50:25 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:49:57 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

int		handle_dollar_2(const char *input,
			int *i, t_buf_info *bi, t_shell *shell);
int		handle_dollar_dq(const char *input,
			int *i, t_buf_info *bi, t_shell *shell);

char	*parse_token(const char *input, int *i,
			int last_exit_status, t_shell *shell);
char	*ft_strndup(const char *s, size_t n);
int		is_whitespace(char c);
int		is_var_char(char c);
int		ensure_buf_capacity(char **buf, int *buf_len, int pos, int needed);
int		append_var(const char *input, int *i, t_buf_info *bi, t_shell *shell);

int		handle_dollar_dq_question(const char *input,
			int *i, t_buf_info *bi, int last_exit_status);
int		handle_dollar_dq_default(const char *input, int *i, t_buf_info *bi);

int		parse_dq(const char *input, int *i,
			t_buf_info *bi, t_shell *shell);
int		parse_sq(const char *input, int *i, t_buf_info *bi);
int		handle_quote(const char *input,
			int *i, t_buf_info *bi, t_shell *shell);
int		handle_regular_char(const char *input, int *i, t_buf_info *bi);
int		handle_special_chars(const char *input, int *i, t_buf_info *bi);

char	**split_redir_token(const char *token);
char	**fix_all_redirs_tokens(char **tokens);

int		count_split_tokens(char **tokens, int *new_count, int i);
int		handle_split_token(char **tokens, char **new_tokens, int *i, int *j);
int		handle_heredoc_token(char **tokens, char **new_tokens, int *i, int *j);
int		copy_split_to_new_tokens(char **new_tokens, int *j, char **split);

char	*initialize_token_builder(t_buf_info *bi);
char	*token_builder(const char *input, int *i,
			int last_exit_status, t_shell *shell);
char	*g_empty_str(void);

int		process_token_char(const char *input,
			int *i, t_buf_info *bi, t_tok_ctx *ctx);

int		process_tokens_loop(char **tokens, char **new_tokens, int *success);
int		fill_new_tokens(char **tokens, char **new_tokens, int new_count);
void	free_split_and_tokens(char **split, char **tokens, int *i);
void	free_str_array_partial(char **arr, int count);

#endif
