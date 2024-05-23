/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:39 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/15 20:19:33 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_append_to_matrix(char **old_matrix, char *line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (old_matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (old_matrix[i])
	{
		new_matrix[i] = ft_strdup(old_matrix[i]);
		i++;
	}
	new_matrix[i++] = ft_strdup(line);
	new_matrix[i] = NULL;
	free_arr(old_matrix);
	return (new_matrix);
}

char	*ms_search_env(t_mshl *ms, char *env_key)
{
	int		i;
	char	**key_value;

	i = 0;
	while (ms->env[i])
	{
		key_value = ft_split(ms->env[i], '=');
		if (ft_strcmp(key_value[0], env_key) == 0)
		{
			free_arr(key_value);
			break ;
		}
		else
			i++;
		free_arr(key_value);
	}
	if (!ms->env[i])
		return (NULL);
	return (ms->env[i]);
}

void	ms_modify_mslvl(t_mshl *ms)
{
	char	*shlvl;
	char	*new_shlvl;
	int		value;
	char	**split;

	shlvl = ms_search_env(ms, "SHLVL");
	if (!shlvl)
	{
		ms->env = ms_append_to_matrix(ms->env, "SHLVL=1");
		return ;
	}
	split = ft_split(shlvl, '=');
	value = ft_atoi(split[1]);
	value++;
	shlvl = ft_itoa(value);
	new_shlvl = ft_strjoin("SHLVL=", shlvl);
	ms_modify_or_add_env(ms, new_shlvl);
	free(shlvl);
	free(new_shlvl);
	free_arr(split);
}
