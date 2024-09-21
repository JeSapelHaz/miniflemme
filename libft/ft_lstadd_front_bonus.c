/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:35:23 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:54:03 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	else
	{
		tmp = *lst;
		*lst = new;
		(*lst)->next = tmp;
	}
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list	*lst;
// 	lst = ft_lstnew("ca va ?");
// 	t_list *new;
// 	new = ft_lstnew("coucou ");

// 	ft_lstadd_front(&lst, new);
// 	while (lst->next != NULL)
// 	{
// 		printf("%s", lst->content);
// 		lst = lst->next;
// 	}
// 	printf("%s", lst->content);
// }
