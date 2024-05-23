/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:13:06 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/08 16:01:46 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_ispace(line[++i]))
			return (false);
	return (true);
}

bool	ms_lexer_main(t_mshl *ms)
{
	if (!ms->line)
		ms_exec_exit_builtin(ms, NULL);
	else if (ms_is_line_empty(ms->line))
		return (true);
	add_history(ms->line);
	if (ms_quotes_err_n_read(ms, ms->line))
		return (false);
	if (ms_stx_err(&ms->token))
		return (false);
	ms_expander_main(ms);
	ms_token_indx(ms);
	ms_parser_main(ms);
	return (true);
}
