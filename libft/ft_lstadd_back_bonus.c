/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:10:00 by alama             #+#    #+#             */
/*   Updated: 2024/04/24 17:45:46 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list *elem = NULL;
// 	t_list *elem2 = ft_lstnew("l1");
// 	t_list *elem3 = ft_lstnew("l2");
// 	t_list *elem4 = ft_lstnew("l3");
// 	ft_lstadd_back(&elem , elem2);
// 	ft_lstadd_back(&elem , elem3);
// 	ft_lstadd_back(&elem , elem4);
// 	while (elem->next != NULL)
// 	{
// 		printf("%s ", elem->content);
// 		elem = elem->next;
// 	}
// 	printf("%s", elem->content);
// }