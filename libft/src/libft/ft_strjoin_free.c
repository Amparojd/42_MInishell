/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:22:31 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/18 20:22:31 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_free_s1(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	free(s1);
	return (new);
}
