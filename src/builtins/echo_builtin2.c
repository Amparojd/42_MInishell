/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:52:52 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/07 23:02:28 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_quote_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (false);
		i++;
	}
	return (true);
}

bool	ms_is_var_no_quotes(t_token *tkns, int index)
{
	t_token	*lst;

	lst = tkns;
	while (lst->next)
	{
		if (lst->index == index)
		{
			if (lst->type == VAR && ms_quote_check(lst->cc))
				return (true);
		}
		lst = lst->next;
	}
	return (false);
}

void	ms_count_no_ws(const char *s, int i, int *len_new, int len)
{
	while (i < len)
	{
		if (!ft_ispace(s[i]) || (i > 0 && !ft_ispace(s[i - 1])))
			(*len_new)++;
		i++;
	}
}

char	*ms_rm_extra_spaces(const char *s)
{
	char	*new_string;
	int		new_len;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	new_len = 0;
	ms_count_no_ws(s, i, &new_len, len);
	new_string = malloc((new_len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!ft_ispace(s[i]) || (i > 0 && !ft_ispace(s[i - 1])))
			new_string[j++] = s[i];
		i++;
	}
	while (j > 0 && ft_ispace(new_string[j - 1]))
		j--;
	new_string[j] = '\0';
	return (new_string);
}
