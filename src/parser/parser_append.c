/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:21:54 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/07 22:58:41 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_append_file(t_fds *fds, char *file_name, char *cc)
{
	if (ms_fds_error2(fds))
		return ;
	fds->outfile = ft_strdup(file_name);
	if (fds->outfile && fds->outfile[0] == '\0' && cc)
	{
		ms_msg_err(cc, NULL, "ambiguous redirect", false);
		return ;
	}
	fds->fd_out = open(fds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fds->fd_out == -1)
		ms_msg_err(fds->outfile, NULL, strerror(errno), false);
}

void	ms_append_parser(t_mshl *ms, t_token **aux)
{
	t_token		*tkn_process;
	t_command	*last_cmd;

	tkn_process = *aux;
	last_cmd = ms_scroll_lstcmd(ms->cmd);
	if (!ms_set_fd_struct(last_cmd))
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	if (!ms->ctrlcheredoc)
		ms_append_file(last_cmd->fds, tkn_process->next->content, \
	tkn_process->next->cc);
	ms_skip_next_token(aux);
}
