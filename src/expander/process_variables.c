/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:04:07 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/11 16:57:39 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = ms_replace_for_xpanded(NULL, str, var_value, index);
		ms_ptr_free(tmp);
	}
	ms_ptr_free(var_value);
	return (str);
}

char	*ms_replace_for_xpanded(t_token **aux, char *content,
			char *value, int scan)
{
	int		trim_len;
	char	*trim_cntnt;

	trim_len = (ft_strlen(content) - ms_var_name_len(content + scan)
			+ ft_strlen(value));
	trim_cntnt = ms_get_var_str(content, value, trim_len, scan);
	if (aux && *aux)
	{
		ms_ptr_free((*aux)->content);
		(*aux)->content = trim_cntnt;
	}
	return (trim_cntnt);
}

bool	ms_xpand_if_null(t_token **aux, char *content, int scan)
{
	int		i;
	int		j;
	int		trim_len;
	char	*trim_cntnt;

	trim_len = ft_strlen(content) - ms_var_name_len(content + scan);
	trim_cntnt = (char *)malloc(sizeof(char) * trim_len + 1);
	if (!trim_cntnt)
		return (false);
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '$' && i == scan)
		{
			i = i + ms_var_name_len(content + scan) + 1;
			if (content[i] == '\0')
				break ;
		}
		trim_cntnt[j++] = content[i++];
	}
	trim_cntnt[j] = '\0';
	ms_ptr_free((*aux)->content);
	(*aux)->content = trim_cntnt;
	return (true);
}

void	ms_process_variables(char *value, t_token **aux, int scan, t_mshl *ms)
{
	if (!value)
	{
		if (!ms_xpand_if_null(aux, (*aux)->content, scan))
		{
			ms_ptr_free(value);
			ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
		}
	}
	else
	{
		if (!ms_replace_for_xpanded(aux, (*aux)->content, value, scan))
		{
			ms_ptr_free(value);
			ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
		}
	}
	ms_ptr_free(value);
}
