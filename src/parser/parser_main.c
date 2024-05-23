/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:48:22 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/12 17:13:32 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_no_arg_prccs(t_mshl *ms)
{
	t_command	*new_cmd;

	if (!ms || !ms->cmd)
		return ;
	new_cmd = ms->cmd;
	while (new_cmd && new_cmd->command)
	{
		if (!new_cmd->args)
		{
			new_cmd->args = malloc(sizeof * new_cmd->args * 2);
			new_cmd->args[0] = ft_strdup(new_cmd->command);
			new_cmd->args[1] = NULL;
		}
		new_cmd = new_cmd->next;
	}
	new_cmd = ms_scroll_lstcmd(ms->cmd);
}

void	ms_parser_main(t_mshl *ms)
{
	t_token	*aux;

	aux = ms->token;
	if (aux->type == END)
		return ;
	while (aux->next)
	{
		if (aux == ms->token)
			ms_addlst_cmd_container(ms, &ms->cmd);
		if (aux->type == WORD || aux->type == VAR)
			ms_word_n_var_parser(ms, &aux);
		else if (aux->type == INPUT)
			ms_infile_parser(ms, &aux);
		else if (aux->type == HEREDOC)
			ms_heredoc_main(ms, &aux);
		else if (aux->type == TRUNC)
			ms_trunc_parser(ms, &aux);
		else if (aux->type == APPEND)
			ms_append_parser(ms, &aux);
		else if (aux->type == PIPE)
			ms_pipe_parser(ms, &aux);
		else if (aux->type == END)
			break ;
	}
	ms_cmd_no_arg_prccs(ms);
}
