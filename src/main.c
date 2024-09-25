/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:01:09 by alama             #+#    #+#             */
/*   Updated: 2024/09/24 16:30:08 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(void)
{
	char	*str;

	printf("belle bito\n");
	while (1)
	{
		str = readline("mini-flemme$ ");
		printf("%s\n", str);
		if (!str || str[0] == '\0')
			break ;
		add_history(str);
		free(str);
	}
	free_history_entry();
	free(str);
	return (0);
}

// t_node			a;
// t_node			b;
// t_node			p;
// a.type = CHAR_NODE;
// a.data.c = 'a';
// b.type = CHAR_NODE;
// b.data.c = 'b';
// p.type = PAIR_NODE;
// p.data.pair.left = &a;
// p.data.pair.right = &b;