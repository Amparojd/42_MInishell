/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:31:06 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/10 11:49:00 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*fwd_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		fwd_lst = ft_lstlast(*lst);
		fwd_lst->next = new;
	}
}
