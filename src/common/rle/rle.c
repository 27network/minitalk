/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:42:53 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 04:55:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <ft/string.h>

static size_t	mt_count_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] == c)
		i++;
	return (i);
}

static char	*mt_encode_rle(char *str)
{
	char	*new_str;
	char	*tmp;
	size_t	i;
	size_t	nb_char;
	size_t	len;

	len = ft_strlen(str);
	new_str = ft_calloc(len * 2 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		nb_char = mt_count_char(&str[i], str[i]);
		tmp = ft_lltoa(nb_char);
		ft_strlcat(new_str, tmp, len + ft_strlen(tmp) + 1);
		free(tmp);
		new_str[ft_strlen(new_str)] = str[i];
		i += nb_char;
	}
	return (new_str);
}

bool	mt_should_rle(char *str, char **rle_string)
{
	int		i;
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (false);
		i++;
	}
	*rle_string = mt_encode_rle(str);
	if (ft_strlen(*rle_string) < len)
		return (true);
	free(*rle_string);
	*rle_string = NULL;
	return (false);
}

static size_t	mt_decoded_size(char *str)
{
	size_t	i;
	size_t	len;
	size_t	cached_len;

	i = 0;
	len = 0;
	cached_len = ft_strlen(str);
	while (i < cached_len)
	{
		len += ft_atoll(&str[i]);
		i += ft_lllen(ft_atoll(&str[i]));
		i++;
	}
	return (len);
}

char	*mt_decode_rle(char *str)
{
	char	*new_str;
	char	c;
	size_t	i;
	size_t	len;
	size_t	cached_len;

	new_str = ft_calloc(mt_decoded_size(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	cached_len = ft_strlen(str);
	i = 0;
	while (i < cached_len)
	{
		len = ft_atoll(&str[i]);
		c = str[i + ft_lllen(len)];
		ft_memset(&new_str[ft_strlen(new_str)], c, len);
		i += ft_lllen(len);
	}
	return (new_str);
}
