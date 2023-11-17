/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:37 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/16 22:39:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_CLIENT
#include "minitalk.h"

static void	mt_write_char(t_mt_printer printer, char c)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	i = 0;
	type_bit_size = sizeof(char) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (c >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

static void	mt_write_size(t_mt_printer printer, size_t value)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	i = 0;
	type_bit_size = sizeof(size_t) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (value >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

void	mt_write_str(t_mt_printer printer, char *str)
{
	mt_write_size(printer, ft_strlen(str));
	while (*str)
		mt_write_char(printer, *str++);
}
