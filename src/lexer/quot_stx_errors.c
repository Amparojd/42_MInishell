/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_stx_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:11:05 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/08 16:28:03 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_quote_stat(int quote_stat, char *line, int scan)
{
	if (line[scan] == '\'' && quote_stat == OK_Q)
		quote_stat = OPN_SQ;
	else if (line[scan] == '\"' && quote_stat == OK_Q)
		quote_stat = OPN_DQ;
	else if (line[scan] == '\'' && quote_stat == OPN_SQ)
		quote_stat = OK_Q;
	else if (line[scan] == '\"' && quote_stat == OPN_DQ)
		quote_stat = OK_Q;
	return (quote_stat);
}

bool	ms_quotes_err_n_read(t_mshl *ms, char *line)
{
	int	start_word;
	int	end_line;
	int	quote_stat;
	int	scan;

	start_word = 0;
	end_line = ft_strlen(line);
	quote_stat = OK_Q;
	scan = -1;
	while (++scan <= end_line)
	{
		quote_stat = ms_quote_stat(quote_stat, line, scan);
		if (quote_stat == OK_Q)
			start_word = ms_chunk_reader(&scan, line, start_word, ms);
	}
	if (quote_stat != OK_Q)
	{
		if (quote_stat == OPN_DQ)
			ms_err_stx_out(ERR_SYNTX_QUO, "\"", true);
		else if (quote_stat == OPN_SQ)
			ms_err_stx_out(ERR_SYNTX_QUO, "\'", true);
		return (true);
	}
	return (false);
}
