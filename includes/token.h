/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:26 by alama             #+#    #+#             */
/*   Updated: 2024/09/26 21:37:17 by alama            ###   ########.fr       */
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
	LPARAN_TOKEN = 3,
	RPARAN_TOKEN = 4,
	SINGLE_QUOTE = 5,
	DOUBLE_QUOTE = 6,
	PIPE = 7,
	O_DIR = 8,
	I_DIR = 9,
	OA_DIR = 10,
	DI_DIR = 11
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

#endif
