/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:39 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/12 20:42:43 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_update_env_vars(t_mshl *ms, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (ms->env[i] && i < size)
	{
		new_env[i] = ft_strdup(ms->env[i]);
		ms_ptr_free(ms->env[i]);
		i++;
	}
	free(ms->env);
	return (new_env);
}

bool	ms_update_or_add_env_var(t_mshl *ms, char *key, char *value)
{
	int		i;
	char	*tmp;

	i = ms_search_env_index(ms->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (i != -1 && ms->env[i])
	{
		ms_ptr_free(ms->env[i]);
		ms->env[i] = ft_strjoin(key, tmp);
	}
	else
	{
		i = ms_count_env_variable(ms->env);
		ms->env = ms_update_env_vars(ms, i + 1);
		if (!ms->env)
			return (false);
		ms->env[i] = ft_strjoin(key, tmp);
	}
	ms_ptr_free(tmp);
	return (true);
}

bool	ms_delete_env_var_pos(t_mshl *ms, int pos)
{
	int	i;
	int	count;

	if (pos > ms_count_env_variable(ms->env))
		return (false);
	i = pos;
	count = pos;
	ms_ptr_free(ms->env[pos]);
	while (ms->env[i + 1])
	{
		ms->env[i] = ft_strdup(ms->env[i + 1]);
		ms_ptr_free(ms->env[i + 1]);
		count++;
		i++;
	}
	ms->env = ms_update_env_vars(ms, count);
	if (!ms->env)
		return (false);
	return (true);
}
