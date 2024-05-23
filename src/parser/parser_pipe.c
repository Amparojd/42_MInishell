/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:24:38 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/11 18:05:32 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe_parser(t_mshl *ms, t_token **token_lst)
{
	t_command	*last_cmd;

	last_cmd = ms_scroll_lstcmd(ms->cmd);
	last_cmd->pipe_output = true;
	ms_addlst_cmd_container(ms, &last_cmd);
	*token_lst = (*token_lst)->next;
}
