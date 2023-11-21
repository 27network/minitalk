/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:42:53 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 01:02:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * @brief Check if the string should be compressed with RLE
 * 
 * @param str 
 * @return bool
 */
bool	mt_should_rle(char *str)
{
	char	*tmp;

	if (ft_strlen(str) < 2)
		return (false);
	tmp = mt_encode_rle(str);
	if (ft_strlen(tmp) < ft_strlen(str))
	{
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

char	*mt_encode_rle(char *str)
{
	char	*new_str;
	char	*tmp;
	char	c;
	size_t	i;
	size_t	j;

	new_str = ft_calloc(ft_strlen(str) * 2 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		c = str[i];
		new_str[j++] = c;
		while (str[i] == c)
			i++;
		ft_strappend(&new_str, tmp = ft_lltoa(i));
		free(tmp);
	}
	return (new_str);
}

char	*mt_decode_rle(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		len = ft_atoi(&str[i + 1]);
		while (len--)
			new_str[j++] = str[i];
		while (ft_isdigit(str[i]))
			i++;
		i++;
	}
	return (new_str);
}
