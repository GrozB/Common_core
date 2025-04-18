/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:53:51 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/15 13:54:05 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <ctype.h>
# include <termios.h>

extern int	g_parent_interrupted;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	int				here_doc_fd;
}	t_redir;

typedef struct s_command
{
	char	**args;
	t_redir	*redirs;
	int		nb_redirs;
	int		is_special_case;
}	t_command;

typedef struct s_shell
{
	int		last_exit_status;
	char	**envp;
}	t_shell;

typedef struct s_tb
{
	const char	*input;
	int			*iptr;
	char		*buf;
	int			pos;
	int			buf_len;
	int			unquoted;
}	t_tb;

typedef struct s_buf_info
{
	char	*buf;
	int		buf_len;
	int		pos;
}	t_buf_info;

typedef struct s_pi_state
{
	int		i;
	int		t;
	int		noexpand;
	char	**tokens;
}	t_pi_state;

typedef struct s_token_info
{
	int	unquoted;
	int	had_var;
	int	last_exit_status;
}	t_token_info;

typedef struct s_dollar_case_info
{
	int	last_exit_status;
	int	*unquoted;
	int	*had_var;
}	t_dollar_case_info;

typedef struct s_quote_state
{
	int	in_squote;
	int	in_dquote;
}	t_quote_state;

typedef struct s_heredoc_info
{
	char	*real_delim;
	int		last_exit_status;
	int		no_expand;
	t_shell	*shell;
}	t_heredoc_info;

typedef struct s_pipeline_child
{
	t_command	*cmd;
	int			index;
	int			count;
	int			prev_fd;
	int			pipe_fd[2];
	pid_t		*pids;
}	t_pipeline_child;

typedef struct s_plchild_data
{
	t_command	*cmd;
	t_command	**cmds;
	int			index;
	int			count;
	int			prev_fd;
	int			*new_prev_fd;
	int			pipe_fd[2];
	pid_t		*child_pid;
	pid_t		*pids;
}	t_plchild_data;

typedef struct s_pipeline_exec
{
	pid_t	*pids;
	int		*prev_fd;
}	t_pipeline_exec;

typedef struct s_var_lookup
{
	int		last_exit_status;
	t_shell	*shell;
}	t_var_lookup;

typedef struct s_sigpair
{
	struct sigaction	new_sa;
	struct sigaction	old_sa;
}	t_sigpair;

typedef struct s_parse_context
{
	t_shell	*shell;
	int		*unquoted;
	int		*had_var;
}	t_parse_context;

typedef struct s_tok_ctx
{
	t_token_info	*ti;
	t_shell			*shell;
}	t_tok_ctx;

// builtin.c
int			my_setenv(t_shell *shell, const char *name,
				const char *value, int overwrite);
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_env(t_shell *shell);
char		*ft_strjoin(char const *s1, char const *s2);
int			builtin_cd(t_shell *shell, char **args);
int			is_valid_identifier(const char *str);
int			builtin_export(t_shell *shell, char **args);
int			is_valid_unset_name(const char *str);
int			builtin_unset(t_shell *shell, char **args);
int			builtin_exit(char **args, t_plchild_data *d, t_shell *shell);
void		my_unsetenv(t_shell *shell, const char *name);
int			ft_isspace(int c);
char		*my_getenv(t_shell *shell, const char *name);

// env_expansion.c
char		*ft_itoa(int n);
int			count_tokens(const char *input,
				int last_exit_status, t_shell *shell);
char		**parse_input(const char *input,
				int last_exit_status, t_shell *shell);
int			is_redirection(const char *token);
int			add_redir(t_command *cmd, t_redir_type type, const char *filename);
char		*remove_quotes(const char *s);
char		**word_split(const char *str);
t_command	*parse_command(char **tokens, int last_exit_status, t_shell *shell);
void		free_command(t_command *cmd);
int			check_syntax_errors(char **tokens);
void		free_str_array(char **arr);

// executor.c
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
void		apply_redirections(t_command *cmd,
				t_plchild_data *d, t_shell *shell);
void		free_commands(t_command **cmds, int num_commands);
char		*find_command_path(t_shell *shell, const char *cmd);
int			is_builtin(char *cmd);
int			execute_builtin(t_command *cmd, t_plchild_data *d, t_shell *shell);
char		*format_token(const char *token);
int			env_count(char **env);
char		**build_envp(t_shell *shell, const char *cmd_path);
void		free_envp(char **envp);
int			execute_command(t_command *cmd, t_shell *shell, t_plchild_data *d);
int			execute_pipeline(t_command **cmds, int n, t_shell *shell);
void		handle_cmd_not_found(t_command *cmd, t_plchild_data *d);

// here_doc.c
void		free_new_tokens_on_failure(char **new_tokens, int count);
char		*expand_vars(const char *line,
				int last_exit_status, t_shell *shell);
void		heredoc_sigint_handler(int sig);
int			handle_here_doc(const char *delimiter,
				int last_exit_status, t_shell *shell);
char		**fix_here_doc_tokens(char **tokens);
int			exit_status(int status);
int			handle_heredoc_line(int pipe_fd, char *line,
				t_heredoc_info *info, t_shell *shell);
int			handle_dollar_question(int *i, t_buf_info *bi,
				int last_exit_status);

// minishell.c
int			count_pipes(char **tokens);
int			check_trailing_pipe(char **tokens);
int			check_pipe_token(char **tokens);
char		**build_segment(char **tokens, int start, int len);
void		free_segment(char **seg);
int			next_pipe(char **tokens, int start);
t_command	*process_segment(char **tokens, int *p, t_shell *shell);
t_command	**split_commands(char **tokens,
				int *num_commands, int last_exit_status, t_shell *shell);
int			check_consecutive_redirs(char **tokens);
int			process_line(char **tokens, t_shell *shell, t_plchild_data *d);
void		sigint_handler(int sig);
int			handle_quote_noexpand(const char *input, int *i, t_buf_info *bi);
int			parse_dq_noexpand(const char *input, int *i, t_buf_info *bi);
int			parse_sq_noexpand(const char *input, int *i, t_buf_info *bi);
int			process_heredoc_input(int pipe_fd,
				t_heredoc_info *info, int *line_number, t_shell *shell);
void		close_inherited_fds(void);
size_t		ft_strcpy(char *dst, const char *src);
void		free_envp(char **envp);

// parse_input.c
char		**split_redir_token(const char *token);
void		free_str_array_partial(char **arr, int count);
int			is_whitespace(char c);
int			is_var_char(char c);
int			ensure_buf_capacity(char **buf, int *buf_len, int pos, int needed);
int			append_var(const char *input, int *i,
				t_buf_info *bi, t_shell *shell);
int			parse_dq(const char *input, int *i, t_buf_info *bi, t_shell *shell);
int			parse_sq(const char *input, int *i, t_buf_info *bi);
int			handle_quote(const char *input, int *i,
				t_buf_info *bi, t_shell *shell);
char		*parse_token(const char *input, int *i,
				int last_exit_status, t_shell *shell);
char		*token_builder(const char *input, int *i,
				int last_exit_status, t_shell *shell);
char		**fix_all_redirs_tokens(char **tokens);
int			fill_new_tokens(char **tokens, char **new_tokens, int new_count);
char		*g_empty_str(void);
char		*ft_strndup(const char *s, size_t len);

// libft
int			ft_isalnum(int i);
int			ft_isalpha(int c);
int			ft_isascii(int i);
int			ft_isdigit(int c);
int			ft_isprint(int i);
char		*ft_itoa(int n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *s1, const void *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int i);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strdup(const char *s);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *litlle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int i);
int			ft_toupper(int i);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
long		ft_atol(const char *str);
int			ft_atoi(const char *str);

#endif
