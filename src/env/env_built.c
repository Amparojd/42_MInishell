/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:39 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/15 19:31:19 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_count_env_variable(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	ms_search_env_index(char **env, char *key)
{
	int		i;
	char	*aux;

	aux = ft_strjoin(key, "=");
	if (!aux)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(aux, env[i], ft_strlen(aux)) == 0)
		{
			ms_ptr_free(aux);
			return (i);
		}
		i++;
	}
	ms_ptr_free(aux);
	return (-1);
}

char	*ms_get_env_var_value(char **env, char *key)
{
	int		i;
	char	*aux;

	aux = ft_strjoin(key, "=");
	if (!aux)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(aux, env[i], ft_strlen(aux)) == 0)
		{
			ms_ptr_free(aux);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	ms_ptr_free(aux);
	return (NULL);
}

bool	ms_check_valid_env_key(char *key)
{
	int	i;

	i = 0;
	if (key == NULL || key[0] == '\0')
		return (false);
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (false);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
