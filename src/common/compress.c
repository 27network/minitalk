/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:23:44 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 05:01:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_COMMON
#include "minitalk.h"

int	mt_compress_data(char *data, char **output)
{
	char	*new_data;
	bool	should_rle;

	should_rle = mt_should_rle(data, &new_data);
	if (!should_rle)
		new_data = ft_strdup(data);
	*output = new_data;
	return (should_rle);
}

int	mt_decompress_data(char *data, char **output)
{
	*output = mt_decode_rle(data);
	return (*output != NULL);
}
