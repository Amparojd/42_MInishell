/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:04:56 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/03 13:17:56 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_quote_detector(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
	return (false);
}

int	ms_process_quotes(t_mshl *ms)
{
	t_token	*aux;

	aux = ms->token;
	while (aux)
	{
		if (ms_quote_detector(aux->content) \
			&& (aux->prev == NULL || (aux->prev && aux->prev->type != HEREDOC)))
			ms_quote_eraser(&aux);
		aux = aux->next;
	}
	return (0);
}
