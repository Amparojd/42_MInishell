/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:17 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/08 18:13:07 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_add_env_quotes(char *env_var)
{
	char	**split;
	char	*quoted_env_var;
	int		i;

	i = 1;
	split = ft_split(env_var, '=');
	quoted_env_var = ft_strjoin(split[0], "=\"");
	while (split[i] && split[i + 1])
	{
		quoted_env_var = strjoin_free_s1(quoted_env_var, split[i++]);
		quoted_env_var = strjoin_free_s1(quoted_env_var, "=");
	}
	if (split[i])
		quoted_env_var = strjoin_free_s1(quoted_env_var, split[i]);
	quoted_env_var = strjoin_free_s1(quoted_env_var, "\"");
	free_arr(split);
	return (quoted_env_var);
}

void	ms_qsort_env(char **env, int n)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				aux = env[i];
				env[i] = env[j];
				env[j] = aux;
			}
			j++;
		}
		i++;
	}
}

int	ms_exp_builtin(t_mshl *ms)
{
	char	*env_quotes;
	int		i;
	int		n;

	i = 0;
	if (!ms->env)
		return (EXIT_FAILURE);
	n = ms_count_env_variable(ms->env);
	ms_qsort_env(ms->env, n);
	i = 0;
	while (i < n)
	{
		env_quotes = ms_add_env_quotes(ms->env[i]);
		printf("declare -x %s\n", env_quotes);
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**key_value_arr(char *key)
{
	char	**arr;
	char	*equal;

	equal = ft_strchr(key, '=');
	if (!equal)
		return (NULL);
	arr = malloc(sizeof(char *) * 3);
	arr[0] = ft_substr(key, 0, equal - key);
	arr[1] = ft_substr(equal, 1, ft_strlen(equal));
	arr[2] = NULL;
	return (arr);
}

int	ms_exec_export_builtin(t_mshl *ms, char **args)
{
	int		i;
	char	**arr;
	int		res;

	res = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (ms_exp_builtin(ms));
	while (args[i])
	{
		if (!ms_check_valid_env_key(args[i]))
		{
			ms_msg_err("export", args[i], "not a valid identifier", \
			false);
			res = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			arr = key_value_arr(args[i]);
			ms_update_or_add_env_var(ms, arr[0], arr[1]);
			ms_ptr_free_arr(arr);
		}
		i++;
	}
	return (res);
}
