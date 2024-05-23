/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:05:01 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/12 18:28:53 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_infile_open(t_fds *fds, char *infile_name, char *cc)
{
	if (ms_fds_error(fds))
		return ;
	fds->infile = ft_strdup(infile_name);
	if (fds->infile && fds->infile[0] == '\0')
	{
		ms_msg_err(cc, NULL, "ambiguous redirect", false);
		fds->error_msg = true;
		return ;
	}
	fds->fd_in = open(fds->infile, O_RDONLY);
	if (fds->fd_in == -1 && fds->error_msg == false)
	{
		ms_msg_err(fds->infile, NULL, strerror(errno), false);
		fds->error_msg = true;
	}
}

void	ms_infile_parser(t_mshl *ms, t_token **aux)
{
	t_token		*aux_aux;
	t_command	*last_cmd;

	aux_aux = *aux;
	last_cmd = ms_scroll_lstcmd(ms->cmd);
	if (last_cmd->fds && last_cmd->fds->error_msg)
	{
		ms_skip_next_token(aux);
		return ;
	}
	if (!ms_set_fd_struct(last_cmd))
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	ms_infile_open(last_cmd->fds, aux_aux->next->content, aux_aux->next->cc);
	ms_skip_next_token(aux);
}
