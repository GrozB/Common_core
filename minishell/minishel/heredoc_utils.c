/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amadiev <amadiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:32:56 by amadiev           #+#    #+#             */
/*   Updated: 2025/04/13 16:42:03 by amadiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	convert_line_number_to_str(int line_number, char *line_number_str)
{
	int		digit_count;
	int		temp_line_number;
	char	*end;
	char	*start;
	char	temp;

	digit_count = 0;
	temp_line_number = line_number;
	while (temp_line_number > 0)
	{
		line_number_str[digit_count++] = '0' + (temp_line_number % 10);
		temp_line_number /= 10;
	}
	line_number_str[digit_count] = '\0';
	start = line_number_str;
	end = line_number_str + digit_count - 1;
	while (start < end)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

void	build_heredoc_warning_message(char *warning_msg,
	int *line_number, t_heredoc_info *info)
{
	char	line_number_str[12];
	int		len;

	len = ft_strcpy(warning_msg, "warning: here-document at line ");
	convert_line_number_to_str(*line_number + 1, line_number_str);
	len += ft_strcpy(warning_msg + len, line_number_str);
	len += ft_strcpy(warning_msg + len, " delimited by end-of-file(wanted '");
	len += ft_strcpy(warning_msg + len, info->real_delim);
	len += ft_strcpy(warning_msg + len, "')\n");
	warning_msg[len] = '\0';
}

int	handle_heredoc_warning(int *line_number, t_heredoc_info *info)
{
	char	warning_msg[256];

	build_heredoc_warning_message(warning_msg, line_number, info);
	write(STDERR_FILENO, warning_msg, ft_strlen(warning_msg));
	return (1);
}
