/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:59:56 by sojala            #+#    #+#             */
/*   Updated: 2025/02/17 11:11:34 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_makestring(char const *s, int start, int len, int i)
{
	if (s[start] == 39 && s[i - 1] == 39)
		return (ft_substr(s, start + 1, len - 2));
	else
		return (ft_substr(s, start, len));
}

static void	ft_setstring(char const *s, int *i, int *len, int *quote)
{
	if (s[*i] == 39)
		*quote = !(*quote);
	*i = *i + 1;
	*len = *len + 1;
}

static char	**ft_makearray_helper(char **array, char const *s,
	char c, int *error)
{
	int	i;
	int	j;
	int	start;
	int	len;
	int	quote;

	i = 0;
	j = -1;
	quote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		len = 0;
		while (s[i] && (s[i] != c || quote))
			ft_setstring(s, &i, &len, &quote);
		array[++j] = ft_makestring(s, start, len, i);
		if (!array[j])
			return (ft_freearray(array, j, error));
	}
	array[++j] = NULL;
	return (array);
}

static	char	**ft_makearray(char const *s, char c, int *error)
{
	char	**array;

	array = malloc((ft_strings(s, c) + 1) * sizeof(char *));
	if (!array)
	{
		*error = 1;
		return (NULL);
	}
	array = ft_makearray_helper(array, s, c, error);
	return (array);
}

char	**ft_pipex_split(char const *s, char c, int *error)
{
	if (!s)
		return (NULL);
	*error = 0;
	return (ft_makearray(s, c, error));
}
