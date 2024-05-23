/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:18:29 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:52:01 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t sizedst)
{
	size_t	sizesrc;
	size_t	i;

	sizesrc = ft_strlen(src);
	i = 0;
	if (sizedst != 0)
	{
		while (i < (sizedst - 1) && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (sizesrc);
}
