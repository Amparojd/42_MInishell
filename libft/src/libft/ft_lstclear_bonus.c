/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:14:57 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:49:16 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*advance;

	advance = NULL;
	while (*lst)
	{
		advance = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		(*lst) = advance;
	}
}
