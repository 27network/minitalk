/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:37 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/19 02:18:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MT_CLIENT
#include "minitalk.h"

static void	mt_write_uint64(t_mt_printer printer, uint64_t value)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	printer(1);
	printer(1);
	i = 0;
	type_bit_size = sizeof(uint64_t) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (value >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

static void	mt_write_uint32(t_mt_printer printer, uint32_t value)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	printer(1);
	printer(0);
	i = 0;
	type_bit_size = sizeof(uint32_t) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (value >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

static void	mt_write_uint16(t_mt_printer printer, uint16_t value)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	printer(0);
	printer(1);
	i = 0;
	type_bit_size = sizeof(uint16_t) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (value >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

static void	mt_write_uint8(t_mt_printer printer, uint8_t value)
{
	uint8_t	type_bit_size;
	int		i;
	int		bit;

	printer(0);
	printer(0);
	i = 0;
	type_bit_size = sizeof(uint8_t) * 8;
	while (i < type_bit_size)
	{
		i++;
		bit = (value >> (type_bit_size - i)) & 1;
		printer(bit);
	}
}

void	mt_write_str(t_mt_printer printer, char *str)
{
	uint8_t	type_bit_size;
	size_t	value;
	int		i;

	value = ft_strlen(str);
	type_bit_size = sizeof(char) * 8;
	if (value > UINT_MAX)
		mt_write_uint64(printer, (uint64_t)value);
	else if (value > USHRT_MAX)
		mt_write_uint32(printer, (uint32_t)value);
	else if (value > UCHAR_MAX)
		mt_write_uint16(printer, (uint16_t)value);
	else
		mt_write_uint8(printer, (uint8_t)value);
	while (*str)
	{
		i = 0;
		while (i++ < type_bit_size)
			printer((*str >> (type_bit_size - i)) & 1);
		str++;
	}
}
