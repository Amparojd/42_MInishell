/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:52:07 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/19 12:52:07 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_dup_env_var_value(t_mshl *ms, char *var_nme)
{
	char	*value;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var_nme);
	while (ms->env[++i])
		if (ft_strncmp(ms->env[i], var_nme, len) == 0)
			break ;
	value = ft_strdup(ms->env[i] + len);
	return (value);
}

bool	ms_is_env_var(t_mshl *ms, char *var_nme)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var_nme);
	while (ms->env[++i])
		if (ft_strncmp(ms->env[i], var_nme, len) == 0)
			return (true);
	return (false);
}

char	*ms_xtract_var_value(t_token *token, char *content, t_mshl *ms)
{
	char	*value;
	char	*var_nme;

	var_nme = ms_xtract_var_name(ms, content);
	if (var_nme && ms_is_env_var(ms, var_nme))
	{
		if (token)
			token->is_env_var = true;
		value = ms_dup_env_var_value(ms, var_nme);
	}
	else if (var_nme && var_nme[0] == '?' && var_nme[1] == '=')
		value = ft_itoa(g_status);
	else
		value = NULL;
	ms_ptr_free(var_nme);
	return (value);
}
