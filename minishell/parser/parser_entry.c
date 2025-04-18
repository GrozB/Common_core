/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgroz <bgroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:59:41 by bgroz             #+#    #+#             */
/*   Updated: 2025/04/14 18:00:02 by bgroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parse_token(const char *input, int *i,
	int last_exit_status, t_shell *shell)
{
	return (token_builder(input, i, last_exit_status, shell));
}
