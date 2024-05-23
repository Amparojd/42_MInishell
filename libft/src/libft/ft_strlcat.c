/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:38:44 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:51:55 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t sizedst)
{
	size_t	a;
	size_t	b;

	if (sizedst <= ft_strlen(dst))
		return (sizedst + ft_strlen(src));
	a = ft_strlen(dst);
	b = 0;
	while (src[b] != 0 && a + 1 < sizedst)
	{
		dst[a] = src[b];
		a++;
		b++;
	}
	dst[a] = 0;
	return (ft_strlen(dst) + ft_strlen(&src[b]));
}
