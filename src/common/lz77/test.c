/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:59:11 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:03:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lz77.h"
#include <ft/print.h>

int	main(void)
{
	char			*str;
	t_lz77_token	*tokens;
	size_t			n;
	size_t			i;

	str = "abracadabra";
	ft_printf("str = %s\n", str);
	tokens = lz77_compress(str, 4, &n);
	i = 0;
	while (i < n)
	{
		ft_printf("tokens[%u] = (%u, %u, %c)\n", i, tokens[i].offset,
			tokens[i].length, tokens[i].next_char);
		i++;
	}
	ft_printf("decoded = %s\n", lz77_decompress(tokens, n));
	return (0);
}
