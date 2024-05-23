/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:55:55 by mlezcano          #+#    #+#             */
/*   Updated: 2024/05/08 12:55:55 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_isalphanum_or__(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (false);
	else
		return (true);
}

int	ms_var_name_len(char *content)
{
	int		i;
	int		len;

	i = 0;
	while (content[i] != '$')
		i++;
	i++;
	if ((content[i] >= '0' && content[i] <= '9') || content[i] == '?')
		return (1);
	len = 0;
	while (content[i])
	{
		if (!ms_isalphanum_or__(content[i]))
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*ms_xtract_var_name(t_mshl *ms, char *content)
{
	char	*var_name;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = -1;
	start = 0;
	while (content[++i])
	{
		if (content[i] == '$')
		{
			start = i + 1;
			break ;
		}
	}
	len = ms_var_name_len(content);
	var_name = ft_substr(content, start, len);
	if (!var_name)
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	tmp = ft_strjoin(var_name, "=");
	ms_ptr_free(var_name);
	var_name = tmp;
	return (var_name);
}
