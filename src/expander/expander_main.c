/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:03:23 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/09 21:08:33 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_mark_variables(t_mshl *ms)
{
	t_token	*aux;
	int		scan;

	aux = ms->token;
	while (aux)
	{
		scan = -1;
		while ((aux)->content[++scan])
		{
			if ((aux)->content[scan] == '$')
			{
				if ((aux)->prev && (aux)->prev->type == HEREDOC)
					break ;
				(aux)->type = VAR;
			}
		}
		aux = aux->next;
	}
}

void	ms_expander_main(t_mshl *ms)
{
	ms_mark_variables(ms);
	ms_scan_variables(ms);
	ms_process_quotes(ms);
}
