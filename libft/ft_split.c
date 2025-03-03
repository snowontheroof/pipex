/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:48:27 by sojala            #+#    #+#             */
/*   Updated: 2025/02/13 14:50:19 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_start(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

static	size_t	ft_strings(char const *s, char c, size_t i)
{
	size_t	strings;

	strings = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			strings++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (strings);
}

static	char	**ft_freearray(char **array, size_t k, int *error)
{
	size_t	i;

	i = 0;
	while (i <= k)
	{
		free (array[i]);
		i++;
	}
	free (array);
	*error = 1;
	return (NULL);
}

static	char	**ft_makearray(char const *s, char c, size_t i, int *error)
{
	char	**array;
	size_t	k;
	size_t	len;

	k = -1;
	array = malloc((ft_strings(s, c, i) + 1) * sizeof(char *));
	if (!array)
	{
		*error = 1;
		return (NULL);
	}
	while (s[i])
	{
		len = 0;
		while (s[i + len] != c && s[i + len])
			len++;
		array[++k] = ft_substr(s, i, len);
		if (!array[k])
			return (ft_freearray(array, k, error));
		i = i + len;
		while (s[i] == c && s[i])
			i++;
	}
	array[++k] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c, int *error)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_start(s, c);
	*error = 0;
	return (ft_makearray(s, c, i, error));
}
