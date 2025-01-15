/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 15:30:16 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	set_ctxt(t_ctxt *ctxt)
{
	ctxt->infile = 0;
	ctxt->outfile = 1;
	ctxt->end[0] = -1;
	ctxt->end[1] = -1;
	ctxt->is_first_o = 0;
	ctxt->is_first_i = 0;
}

void	ft_exe(t_node *node, char **env)
{
	t_node	*left;
	t_node	*right;
	t_ctxt	ctxt;

	set_ctxt(&ctxt);
	if (node->type == STR_NODE)
		first_process(node, env);
	else if (node->type == PAIR_NODE)
	{
		left = node->data.pair.left;
		right = node->data.pair.right;
		if (node->data.pair.opera[0] == '|')
			exe_pipe(node, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
			input_dir(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
			output_dir(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
			output_append(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
			di_to_dir(right, left, env, &ctxt);
	}
}
