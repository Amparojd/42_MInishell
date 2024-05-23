/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:26:22 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/08 21:04:42 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_oprtr_to_tkn(t_token **tkns, char *line, int scan, int oprtr_type)
{
	int		i;
	char	*oprtr;

	i = 0;
	if (oprtr_type == APPEND || oprtr_type == HEREDOC)
	{
		oprtr = malloc(sizeof(char) * 3);
		if (!oprtr)
			return (false);
		while (i < 2)
			oprtr[i++] = line[scan++];
		oprtr[i] = '\0';
		ms_add_tkn_lst(tkns, ms_tkn_creat(oprtr, NULL, oprtr_type, OK_Q));
	}
	else
	{
		oprtr = malloc(sizeof(char) * 2);
		if (!oprtr)
			return (false);
		while (i < 1)
			oprtr[i++] = line[scan++];
		oprtr[i] = '\0';
		ms_add_tkn_lst(tkns, ms_tkn_creat(oprtr, NULL, oprtr_type, OK_Q));
	}
	return (true);
}

bool	ms_word_to_tkn(t_token **tkns, char *line, int scan, int start_word)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (scan - start_word + 1));
	if (!word)
		return (false);
	while (start_word < scan)
	{
		word[i] = line[start_word];
		start_word++;
		i++;
	}
	word[i] = '\0';
	ms_add_tkn_lst(tkns, ms_tkn_creat (word, ft_strdup(word), WORD, OK_Q));
	return (true);
}

int	ms_chck_oprtr_type(char *line, int scan)
{
	int	size;

	size = ft_strlen(line + scan);
	if (((line[scan] > 8 && line[scan] < 14) || line[scan] == 32))
		return (SPACES);
	else if (line[scan] == '|')
		return (PIPE);
	else if (size >= 3 && line[scan] == '<' && line[scan + 1] == '<')
		return (HEREDOC);
	else if (size >= 3 && line[scan] == '>' && line[scan + 1] == '>')
		return (APPEND);
	else if (size >= 2 && line[scan] == '<')
		return (INPUT);
	else if (size >= 2 && line[scan] == '>')
		return (TRUNC);
	else if (line[scan] == '<' || line[scan] == '>')
		return (FAILURE);
	else if (line[scan] == '\0')
		return (END);
	else
		return (0);
}

int	ms_chunk_reader(int *scan, char *line, int start_word, t_mshl *ms)
{
	int	oprtr;

	oprtr = ms_chck_oprtr_type(line, (*scan));
	if (oprtr)
	{
		if ((*scan) != 0 && !ms_chck_oprtr_type(line, (*scan) - 1))
			if (!ms_word_to_tkn(&ms->token, line, (*scan), start_word))
				ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
		if (oprtr && oprtr != SPACES)
		{
			if (!ms_oprtr_to_tkn(&ms->token, line, (*scan), oprtr))
				ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
			if (oprtr == APPEND || oprtr == HEREDOC)
				(*scan)++;
		}
		start_word = (*scan) + 1;
	}
	return (start_word);
}
