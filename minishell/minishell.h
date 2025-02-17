/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:59:18 by bgroz             #+#    #+#             */
/*   Updated: 2025/02/17 17:14:40 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_command
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
}	t_command;

char **parse_input(const char *input, int last_exit_status);
t_command	*parse_command(char **tokens);
void	free_command(t_command *cmd);
void	free_commands(t_command **cmds, int num_commands);
int		execute_command(t_command *cmd);
int		execute_pipeline(t_command **cmds, int n);

#endif


