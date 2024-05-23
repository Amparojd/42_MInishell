/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_filler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:16:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/23 16:16:48 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_word_n_var_counter(t_token *aux)
{
	int	i;

	i = 0;
	while (aux && (aux->type == WORD || aux->type == VAR))
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

char	**ms_create_table(
	int args_amnt, char **args_table, t_command *cmd, t_token **arg_list)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = *arg_list;
	while (i < args_amnt)
	{
		args_table[i] = cmd->args[i];
		i++;
	}
	while (aux->type == WORD || aux->type == VAR)
	{
		args_table[i] = ft_strdup(aux->content);
		i++;
		aux = aux->next;
	}
	args_table[i] = NULL;
	return (args_table);
}

void	ms_rm_echo_empty_words(t_token **arg_list)
{
	t_token	*aux;

	aux = *arg_list;
	while (aux->type == WORD || aux->type == VAR)
	{
		if (aux->type == VAR && aux->content[0] == '\0' && \
		!aux->has_quotes)
		{
			aux = aux->next;
			if (aux == (*arg_list)->next)
				(*arg_list) = (*arg_list)->next;
			ms_del_one_node_tkn(aux->prev, ms_ptr_free);
		}
		else
			aux = aux->next;
	}
}
