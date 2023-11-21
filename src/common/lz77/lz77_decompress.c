/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lz77_decompress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:57:11 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 06:05:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lz77.h"

static void	add_char(char **str, size_t *len, char c)
{
	char	*new_str;
	size_t	i;

	new_str = ft_calloc(*len + 1, sizeof(char));
	if (!new_str)
		return ;
	i = 0;
	while (i < *len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	free(*str);
	*str = new_str;
	*len += 1;
}

static char	*strnjoin(char *s1, char *s2, size_t n)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = ft_calloc(ft_strlen(s1) + n + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < n)
	{
		new_str[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (new_str);
}

char	*lz77_decompress(t_lz77_token *tokens, size_t ntokens)
{
	char	*str;
	size_t	len;
	size_t	i;

	str = ft_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	len = 1;
	while (i < ntokens)
	{
		if (tokens[i].length == 0)
			add_char(&str, &len, tokens[i].next_char);
		else
			str = strnjoin(str, str + tokens[i].offset, tokens[i].length);
		i++;
	}
	free(tokens);
	return (str);
}
