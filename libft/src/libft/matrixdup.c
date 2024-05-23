/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:14:40 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/29 18:25:52 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**matrixdup(char **arr)
{
	char	**newarr;
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	newarr = ft_calloc(sizeof(char *), i + 1);
	if (!newarr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		newarr[i] = ft_strdup(arr[i]);
		if (!newarr[i])
		{
			free_arr(newarr);
			return (NULL);
		}
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}
