/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:10:25 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:51:33 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, len - 1);
	s2[len - 1] = '\0';
	return (s2);
}
