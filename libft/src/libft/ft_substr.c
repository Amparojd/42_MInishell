/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:31:40 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/09 21:51:23 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size < start)
		return (ft_strdup(""));
	else if (start + len > size)
		len = size - start;
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, len + 1);
	return (s2);
}

/**
*DESCRIPTION
*Reserve (with malloc(3)) and return a substring of the string 's'.
*The substring starts from index 'start' and has a maximum length 'len'.
*
*RETURN VALUES
*The resulting substring.
*NULL if memory reservation fails.
*
*PARAMETERS
*s: The string from which to create the substring. start:
*The index of the character in 's' from which to start the substring.
*len: The maximum length of the substring.
**/
