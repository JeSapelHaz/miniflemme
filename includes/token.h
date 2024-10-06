/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:26 by alama             #+#    #+#             */
/*   Updated: 2024/10/05 16:06:20 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "mini_shell.h"

typedef enum s_token_type
{
	END_TOKEN = 0,
	CHAR_TOKEN = 1,
	SPACE_TOKEN = 2,
	PAREN_TOKEN = 3,
	SINGLE_QUOTE = 4,
	DOUBLE_QUOTE = 5,
	PIPE = 6,
	O_DIR = 7,	// output directory
	I_DIR = 8,	// input directory
	OA_DIR = 9,	// output append 
	DI_DIR = 10	// directory to directory
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	PAIR_NODE,
	CHAR_NODE 
}						t_node_type;

typedef struct s_node	t_node;

typedef struct s_pair_value
{
	t_node				*left;
	t_node				*right;
}						t_pair_value;

typedef union u_node_value
{
	t_pair_value		pair;
	char				*c;
}						t_node_value;

struct					s_node
{
	t_node_type			type;
	t_node_value		data;
};

#endif
