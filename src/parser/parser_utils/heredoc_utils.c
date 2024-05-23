/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:38:20 by mlezcano          #+#    #+#             */
/*   Updated: 2024/05/09 12:38:20 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_g_status_handler(char **line, t_mshl *ms)
{
	(void)ms;
	if (*line == NULL && g_status == 1)
		g_status = 1;
	else if (*line == NULL)
	{
		g_status = 0;
		ms->ctrlcheredoc = true;
	}
	return (false);
}

bool	ms_loop_breaker(t_mshl *ms, char **line, t_fds *fds, bool *success)
{
	if ((*line == NULL && g_status == 1) || *line == NULL)
	{
		*success = ms_g_status_handler(line, ms);
		return (BREAK);
	}
	if (ft_strcmp(*line, fds->heredoc_del) == 0)
	{
		*success = true;
		return (BREAK);
	}
	if (fds->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = ms_heredoc_xpndr_main(ms, *line);
		if (!(*line))
		{
			ms_ptr_free(*line);
			*success = false;
			return (BREAK);
		}
	}
	return (GO);
}

void	ms_quit_newline_char(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
