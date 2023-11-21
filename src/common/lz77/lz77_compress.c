/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lz77_compress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:47:47 by kiroussa          #+#    #+#             */
/*   Updated: 2023/11/21 14:25:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lz77.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

#define WINDOW_SIZE 64
#define LOOKAHEAD_BUFFER_SIZE 15

/*
 def findLongestMatch(self, data, current_position):
		""" 
		Finds the longest match to a substring starting at the current_position 
		in the lookahead buffer from the history window
		"""
		end_of_buffer = min(current_position + self.lookahead_buffer_size, len(data) + 1)

		best_match_distance = -1
		best_match_length = -1

		# Optimization: Only consider substrings of length 2 and greater, and just 
		# output any substring of length 1 (8 bits uncompressed is better than 13 bits
		# for the flag, distance, and length)
		for j in range(current_position + 2, end_of_buffer):

			start_index = max(0, current_position - self.window_size)
			substring = data[current_position:j]

			for i in range(start_index, current_position):

				repetitions = len(substring) // (current_position - i)

				last = len(substring) % (current_position - i)

				matched_string = data[i:current_position] * repetitions + data[i:i+last]

				if matched_string == substring and len(substring) > best_match_length:
					best_match_distance = current_position - i 
					best_match_length = len(substring)

		if best_match_distance > 0 and best_match_length > 0:
			return (best_match_distance, best_match_length)
		return None


   */

static t_lz77_token	*lz77_token_create

static t_lz77_token	*lz77_longest_match(const char *data, size_t current_position)
{
	size_t	end_of_buffer;
	size_t	best_match_distance;
	size_t	best_match_length;
	size_t	j;
	size_t	start_index;
	char	*substring;
	size_t	i;
	size_t	repetitions;
	size_t	last;
	char	*matched_string;

	end_of_buffer = ft_min(current_position + LOOKAHEAD_BUFFER_SIZE,
			ft_strlen(data) + 1);
	best_match_distance = -1;
	best_match_length = -1;
	j = current_position + 2;
	while (j < end_of_buffer)
	{
		start_index = ft_max(0, current_position - WINDOW_SIZE);
		substring = ft_substr(data, current_position, j);
		i = start_index;
		while (i < current_position)
		{
			repetitions = ft_strlen(substring) / (current_position - i);
			last = ft_strlen(substring) % (current_position - i);
			matched_string = ft_strjoin(ft_substr(data, i, current_position),
					ft_substr(data, i, i + last));
			if (ft_strcmp(matched_string, substring) == 0
				&& ft_strlen(substring) > best_match_length)
			{
				best_match_distance = current_position - i;
				best_match_length = ft_strlen(substring);
			}
			i++;
		}
		j++;
	}
	if (best_match_distance > 0 && best_match_length > 0)
		return (lz77_token_create(best_match_distance, best_match_length));
	return (NULL);
}
