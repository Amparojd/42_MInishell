/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:01:10 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/15 11:45:50 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_split_in_args(t_command *new_cmd, char *tkn_cntnt, t_mshl *ms)
{
	char		**splited_cntn;
	t_token		*args_list;
	t_token		*free_tkn_ptr;
	int			i;

	splited_cntn = ft_split(tkn_cntnt, ' ');
	if (!splited_cntn)
		return ;
	new_cmd->command = ft_strdup(splited_cntn[0]);
	args_list = NULL;
	if (splited_cntn[1])
	{
		i = 0;
		while (splited_cntn[++i])
			ms_add_tkn_lst(&args_list,
				ms_tkn_creat(ft_strdup(splited_cntn[i]), NULL, WORD, OK_Q));
	}
	ms_add_tkn_lst(&args_list, ms_tkn_creat(NULL, NULL, END, OK_Q));
	if (!ms_cmd_arg_filler(&args_list, new_cmd))
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	free_tkn_ptr = args_list;
	ms_del_all_nodes_tkn(&free_tkn_ptr, &ms_ptr_free);
	ms_ptr_free_arr(splited_cntn);
}

bool	ms_is_there_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			return (true);
	return (false);
}

void	ms_word_n_var_parser(t_mshl *ms, t_token **aux)
{
	t_token		*token;
	t_command	*new_cmd;

	token = *aux;
	while (token->type == WORD || token->type == VAR)
	{
		new_cmd = ms_scroll_lstcmd(ms->cmd);
		if (token->prev == NULL || (token->prev && token->prev->type == PIPE)
			|| new_cmd->command == NULL || new_cmd->command[0] == '\0')
		{
			if (token->type == VAR && ms_is_there_space(token->content))
				ms_split_in_args(new_cmd, token->content, ms);
			else
				new_cmd->command = ft_strdup(token->content);
			token = token->next;
		}
		else if (!ms_cmd_arg_filler(&token, new_cmd))
			ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	}
	*aux = token;
}
