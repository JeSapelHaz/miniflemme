/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:26 by alama             #+#    #+#             */
/*   Updated: 2024/09/25 15:41:25 by alama            ###   ########.fr       */
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
	RPAREN_TOKEN = 4
}	t_token_type;

typedef struct s_token
{
	t_koen_type	type;
	char	*lexeme;
}	t_token;

#endif
