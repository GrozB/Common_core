NAME     := minishell

# -------------------- Colors --------------------
RESET   = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
CYAN    = \033[1;36m
MAGENTA = \033[1;35m

# -------------------- Sources --------------------
SRCS    = parser/parser_dollar_expand.c \
		  parser/parser_entry.c \
		  parser/parser_env_utils.c \
		  parser/parser_handle_dollar.c \
		  parser/parser_quotes_regular.c \
		  parser/parser_redir_fix.c \
		  parser/parser_redir_helpers.c \
		  parser/parser_token_builder.c \
		  parser/parser_token_cases.c \
		  parser/parser_token_loop.c \
		  executor/exec_apply.c \
		  executor/exec_builtin_redir.c \
		  executor/exec_builtin.c \
		  executor/exec_cmd_missing.c \
		  executor/exec_cmd_path.c \
		  executor/exec_env_build.c \
		  executor/exec_env_helper.c \
		  executor/exec_external_exec.c \
		  executor/exec_format.c \
		  executor/exec_path_build.c \
		  executor/exec_path_find.c \
		  executor/exec_pipeline_exec.c \
		  executor/exec_pipeline_fork.c \
		  executor/exec_pipeline_helpers.c \
		  executor/exec_redirections.c \
		  executor/exec_utils.c \
		  executor/exec_utils2.c \
		  builtin/builtin_basic.c \
		  builtin/builtin_cd_and_error.c \
		  builtin/builtin_cd.c \
		  builtin/builtin_env_utils.c \
		  builtin/builtin_exit_utils.c \
		  builtin/builtin_exit.c \
		  builtin/builtin_export_utils.c \
		  builtin/builtin_export_utils2.c \
		  builtin/builtin_export.c \
		  builtin/builtin_unset.c \
		  builtin/builtin_utils.c \
		  builtin/builtin_rest.c \
		  heredoc/heredoc_delimiter.c \
		  heredoc/heredoc_expand.c \
		  heredoc/heredoc_fix_tokens.c \
		  heredoc/heredoc_handle_line.c \
		  heredoc/heredoc_line_utils.c \
		  heredoc/heredoc_main.c \
		  heredoc/heredoc_utils.c \
		  env_expansion/argument_allocation.c \
		  env_expansion/argument_finalize.c \
		  env_expansion/command_parser.c \
		  env_expansion/filename_utils.c \
		  env_expansion/heredoc_redir.c \
		  env_expansion/itoa_utils.c \
		  env_expansion/quote_noexpand.c \
		  env_expansion/redirection_utils.c \
		  env_expansion/string_utils.c \
		  env_expansion/syntax_checker1.c \
		  env_expansion/syntax_checker2.c \
		  env_expansion/tb_token1.c \
		  env_expansion/tb_token2.c \
		  env_expansion/token_collection1.c \
		  env_expansion/token_collection2.c \
		  env_expansion/token_counter.c \
		  env_expansion/word_split_utils.c \
		  minishel/command_array.c \
		  minishel/command_processing.c \
		  minishel/env.c \
		  minishel/execution.c \
		  minishel/heredoc_exec.c \
		  minishel/heredoc_utils.c \
		  minishel/main.c \
		  minishel/pipe_errors.c \
		  minishel/redir_errors.c \
		  minishel/segment.c \
		  minishel/signals.c \
		  minishel/token_utils.c \

LIBFT    := libft/libft.a

# -------------------- Objects --------------------
OBJS    := $(SRCS:.c=.o)

# -------------------- Compiler & Flags --------------------
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
LDFLAGS := -lreadline

# -------------------- Rules --------------------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(CYAN)Linking $(RESET)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$(shell echo $(NAME) | tr a-z A-Z)$(GREEN) is ready!$(RESET)"

$(LIBFT):
	@echo "$(CYAN)Building $(RESET)LIBFT"
	@$(MAKE) -C libft --no-print-directory -s

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Removing $(YELLOW)object files$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) clean -C libft --no-print-directory -s

fclean: clean
	@echo "$(RED)Removing $(RESET)$(shell echo $(NAME) | tr a-z A-Z)"
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft --no-print-directory -s

re: fclean all

.PHONY: all clean fclean re
