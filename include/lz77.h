/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lz77.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:48:24 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:02:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LZ77_H
# define LZ77_H

# include <ft/mem.h>
# include <ft/print.h>
# include <ft/string.h>
# include <stdlib.h>

typedef struct s_lz77_token
{
	int		offset;
	int		length;
	char	next_char;
}	t_lz77_token;

t_lz77_token	*lz77_compress(const char *str, size_t window, size_t *ntokens);
char			*lz77_decompress(t_lz77_token *tokens, size_t ntokens);

#endif // LZ77_H
