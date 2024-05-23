/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:54:35 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:56:10 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*pnt;

	pnt = malloc(nitems * size);
	if (pnt == 0)
		return (pnt);
	ft_bzero(pnt, nitems * size);
	return (pnt);
}
