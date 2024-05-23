/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stx_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:59 by mlezcano          #+#    #+#             */
/*   Updated: 2024/05/09 17:07:59 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_stx_error_cases(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type >= PIPE)
		{
			g_status = ERR_PIPE_STX;
			return (true);
		}
		if (token->type > PIPE && token->prev->type > PIPE)
		{
			g_status = ERR_PIPE_STX;
			return (true);
		}
		if (token->type == END && token->prev->type >= PIPE)
		{
			g_status = ERR_PIPE_STX;
			return (true);
		}
	}
	return (false);
}

bool	ms_stx_err_iterator(t_token **token_list)
{
	t_token	*aux;

	aux = *token_list;
	while (aux)
	{
		if (ms_stx_error_cases(aux))
		{
			if (aux->type == END && aux->prev && aux->prev->type > PIPE)
				ms_err_stx_out(ERR_SYNTX_TKN, "newline", true);
			else if (aux->type == END && aux->prev && aux->prev->type == PIPE)
				ms_err_stx_out(ERR_SYNTX_TKN, aux->prev->content, true);
			else
				ms_err_stx_out(ERR_SYNTX_TKN, aux->content, true);
			return (true);
		}
		aux = aux->next;
	}
	return (false);
}

bool	ms_stx_err(t_token **token_list)
{
	t_token	*aux;

	aux = *token_list;
	if (aux->type == PIPE)
	{
		ms_err_stx_out(ERR_SYNTX_TKN, aux->content, true);
		g_status = ERR_PIPE_STX;
		return (true);
	}
	while (aux)
	{
		if (ms_stx_err_iterator(&aux))
			return (true);
		aux = aux->next;
	}
	return (false);
}
