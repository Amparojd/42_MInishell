/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:42:26 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/05 17:17:01 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_cmd_arg_only_fill(t_token **arg_list, t_command *cmd, bool is_echo)
{
	int		var_word_amnt;
	t_token	*aux;
	int		args_amnt;
	char	**args_table;

	if (is_echo)
		ms_rm_echo_empty_words(arg_list);
	aux = *arg_list;
	var_word_amnt = 0;
	while (aux && (aux->type == WORD || aux->type == VAR))
	{
		var_word_amnt++;
		aux = aux->next;
	}
	args_amnt = 0;
	while (cmd->args[args_amnt])
		args_amnt++;
	args_table = malloc(sizeof(char *) * (var_word_amnt + args_amnt + 1));
	if (!args_table)
		return (false);
	args_table = ms_create_table(args_amnt, args_table, cmd, arg_list);
	free(cmd->args);
	cmd->args = args_table;
	*arg_list = aux;
	return (true);
}

bool	ms_cmd_arg_creat_n_fill(t_token **arg_list, \
	t_command *cmd, bool is_echo)
{
	int		arg_amnt;
	t_token	*aux;
	int		i;

	if (is_echo)
		ms_rm_echo_empty_words(arg_list);
	aux = *arg_list;
	arg_amnt = ms_word_n_var_counter(aux);
	cmd->args = malloc(sizeof(char *) * (arg_amnt + 2));
	if (!cmd->args)
		return (false);
	i = 0;
	cmd->args[i] = ft_strdup(cmd->command);
	i++;
	while (aux->type == WORD || aux->type == VAR)
	{
		cmd->args[i] = ft_strdup(aux->content);
		i++;
		aux = aux->next;
	}
	cmd->args[i] = NULL;
	*arg_list = aux;
	return (true);
}

bool	ms_cmd_arg_filler(t_token **arg_list, t_command *cmd)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
	{
		if (!(cmd->args))
			return (ms_cmd_arg_creat_n_fill(arg_list, cmd, true));
		else
			return (ms_cmd_arg_only_fill(arg_list, cmd, true));
	}
	else
	{
		if (!(cmd->args))
			return (ms_cmd_arg_creat_n_fill(arg_list, cmd, false));
		else
			return (ms_cmd_arg_only_fill(arg_list, cmd, false));
	}
	return (true);
}
