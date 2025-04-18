/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:44:08 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 14:29:45 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_expansion.h"

int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

int	add_redir(t_command *cmd, t_redir_type type, const char *filename)
{
	t_redir	*new_redirs;
	int		i;

	new_redirs = malloc(sizeof(t_redir) * (cmd->nb_redirs + 1));
	if (!new_redirs)
		return (0);
	i = 0;
	while (i < cmd->nb_redirs)
	{
		new_redirs[i] = cmd->redirs[i];
		i++;
	}
	new_redirs[i].type = type;
	new_redirs[i].filename = ft_strdup(filename);
	new_redirs[i].here_doc_fd = -1;
	free(cmd->redirs);
	cmd->redirs = new_redirs;
	cmd->nb_redirs += 1;
	return (1);
}

char	*remove_quotes(const char *s)
{
	size_t	len;
	char	*res;

	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '\"' && s[len - 1] == '\"')
			|| (s[0] == '\'' && s[len - 1] == '\'')))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy(res, s + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	return (ft_strdup(s));
}
