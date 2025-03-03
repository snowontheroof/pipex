/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:48:27 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 15:41:35 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_freearray(char **array, int j, int *error)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free (array[i]);
		i++;
	}
	free (array);
	*error = 1;
	return (NULL);
}

int	ft_checkquote(char const *s, int i)
{
	while (s[i])
	{
		if (s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strings(char const *s, char c)
{
	int	i;
	int	strings;

	i = 0;
	strings = 0;
	while (s[i])
	{
		if (s[i] == 39 && s[i - 1] == c && ft_checkquote(s, i + 1))
		{
			strings++;
			i++;
			while (s[i] && s[i] != 39)
				i++;
			i++;
		}
		else if (s[i] != c)
		{
			strings++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (strings);
}
