/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_eraser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:44 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/08 16:28:03 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_skip_quot_n_close(t_token **aux, int *pos)
{
	if (((*aux)->content[*pos] == '\'' && (*aux)->var_q_stat == OPN_SQ)
		|| ((*aux)->content[*pos] == '\"' \
		&& (*aux)->var_q_stat == OPN_DQ))
	{
		(*aux)->var_q_stat = OK_Q;
		(*pos)++;
		return (true);
	}
	else
		return (false);
}

void	ms_skip_quot_n_open(t_token **aux, int *pos)
{
	if ((*aux)->content[*pos] == '\'')
		(*aux)->var_q_stat = OPN_SQ;
	if ((*aux)->content[*pos] == '\"')
		(*aux)->var_q_stat = OPN_DQ;
	(*pos)++;
}

bool	ms_is_quote_here(t_token **aux, int pos)
{
	if (((*aux)->content[pos] == '\'' || (*aux)->content[pos] == '\"')
		&& (*aux)->var_q_stat == OK_Q)
		return (true);
	else
		return (false);
}

int	ms_len_wthout_quot(char *content, int len)
{
	int	status;
	int	i;

	status = OK_Q;
	i = 0;
	while (content[i])
	{
		if ((content[i] == '\'' || content[i] == '\"') && status == OK_Q)
		{
			if (content[i] == '\'')
				status = OPN_SQ;
			if (content[i] == '\"')
				status = OPN_DQ;
			i++;
		}
		else if ((content[i] == '\'' && status == OPN_SQ)
			|| (content[i] == '\"' && status == OPN_DQ))
		{
			status = OK_Q;
			i++;
		}
		len++;
		i++;
	}
	return (len);
}

void	ms_quote_eraser(t_token **aux)
{
	int		i;
	int		j;
	char	*noq_str;

	i = 0;
	j = 0;
	noq_str = malloc(sizeof(char) * ms_len_wthout_quot((*aux)->content, i) + 1);
	while ((*aux)->content[i])
	{
		if (ms_is_quote_here(aux, i))
			ms_skip_quot_n_open(aux, &i);
		else if (ms_skip_quot_n_close(aux, &i))
			continue ;
		else
			noq_str[j++] = (*aux)->content[i++];
	}
	noq_str[j] = '\0';
	ms_ptr_free((*aux)->content);
	(*aux)->content = noq_str;
	(*aux)->has_quotes = true;
}
