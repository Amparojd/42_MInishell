/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_trunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:37:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/25 18:37:48 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_create_trunc(t_fds *fds, char *file_name, char *cc)
{
	if (ms_fds_error2(fds))
		return ;
	fds->outfile = ft_strdup(file_name);
	if (fds->outfile && fds->outfile[0] == '\0' && fds->error_msg == false)
	{
		ms_msg_err(cc, NULL, "ambiguous redirect", false);
		fds->error_msg = true;
		return ;
	}
	fds->fd_out = open(fds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fds->fd_out == -1 && fds->error_msg == false)
	{
		ms_msg_err(fds->outfile, NULL, strerror(errno), false);
		fds->error_msg = true;
	}
}

void	ms_trunc_parser(t_mshl *ms, t_token **aux)
{
	t_token		*tkn_process;
	t_command	*last_cmd;

	tkn_process = *aux;
	last_cmd = ms_scroll_lstcmd(ms->cmd);
	if (last_cmd->fds && last_cmd->fds->error_msg)
	{
		ms_skip_next_token(aux);
		return ;
	}
	if (!ms_set_fd_struct(last_cmd))
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	if (!ms->ctrlcheredoc)
		ms_create_trunc(last_cmd->fds, tkn_process->next->content, \
	tkn_process->next->cc);
	ms_skip_next_token(aux);
}
