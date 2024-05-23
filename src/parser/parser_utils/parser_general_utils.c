/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:23:35 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/26 16:55:05 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_fds_error(t_fds *fds)
{
	if (fds->infile)
	{
		if (fds->fd_in == -1 || (fds->outfile && fds->fd_out == -1))
			return (true);
		if (fds->heredoc_del)
		{
			ms_ptr_free(fds->heredoc_del);
			fds->heredoc_del = NULL;
			unlink(fds->infile);
		}
		ms_ptr_free(fds->infile);
		close(fds->fd_in);
	}
	return (false);
}

bool	ms_fds_error2(t_fds *fds)
{
	if (fds->outfile)
	{
		if (fds->fd_out == -1 || (fds->infile && fds->fd_in == -1))
			return (true);
		ms_ptr_free(fds->outfile);
		close(fds->fd_out);
	}
	return (false);
}

t_command	*ms_scroll_lstcmd(t_command *aux)
{
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	ms_skip_next_token(t_token **aux)
{
	if ((*aux)->next->next)
		*aux = (*aux)->next->next;
	else
		*aux = (*aux)->next;
}
