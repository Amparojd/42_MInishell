/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:00:30 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/09 21:03:31 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_addspace_btwn_words(char **words)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (words[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(words[0]);
		else
		{
			str = ft_strjoin(tmp, words[i]);
			ms_ptr_free(tmp);
		}
		if (words[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			ms_ptr_free(tmp);
		}
	}
	ms_ptr_free_arr(words);
	return (str);
}

char	*ms_heredoc_var_xpndr(t_mshl *ms, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '$'
			&& !ms_dollar_error(var, i))
			var = replace_str_heredoc(var, \
			ms_xtract_var_value(NULL, var + i, ms), i);
		else
			i++;
	}
	return (var);
}

char	*ms_heredoc_xpndr_main(t_mshl *ms, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = ms_heredoc_var_xpndr(ms, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (ms_addspace_btwn_words(words));
}
