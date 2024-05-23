/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:39:00 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/11 16:37:42 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_between_d_quot(char *content, int scan)
{
	if (scan > 0)
	{
		if (content[scan - 1] == '\"' && content[scan + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	ms_is_bad_char_next(char next)
{
	if (next == '$' || next == ' ' || next == '=' || next == '\0')
		return (true);
	else
		return (false);
}

bool	ms_dollar_error(char *content, int scan)
{
	if ((ms_is_bad_char_next(content[scan + 1])) \
		|| (ms_is_between_d_quot(content, scan)))
		return (true);
	else
		return (false);
}

void	ms_quote_stat_expndr(t_token **node, char scan)
{
	if (scan == '\'' && (*node)->var_q_stat == OK_Q)
		(*node)->var_q_stat = OPN_SQ;
	else if (scan == '\"' && (*node)->var_q_stat == OK_Q)
		(*node)->var_q_stat = OPN_DQ;
	else if (scan == '\'' && (*node)->var_q_stat == OPN_SQ)
		(*node)->var_q_stat = OK_Q;
	else if (scan == '\"' && (*node)->var_q_stat == OPN_DQ)
		(*node)->var_q_stat = OK_Q;
}

void	ms_scan_variables(t_mshl *ms)
{
	t_token	*aux;
	int		scan;

	aux = ms->token;
	while (aux)
	{
		if (aux->type == VAR)
		{
			scan = 0;
			while (aux->content[scan])
			{
				ms_quote_stat_expndr(&aux, aux->content[scan]);
				if ((aux->content[scan] == '$' \
				&& !ms_dollar_error(aux->content, scan)) \
				&& (aux->var_q_stat == OK_Q || aux->var_q_stat == OPN_DQ))
					ms_process_variables(ms_xtract_var_value \
					(aux, aux->content + scan, ms), &aux, scan, ms);
				else
					scan++;
			}
		}
		aux = aux->next;
	}
}
