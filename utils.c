/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:00:17 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 17:07:29 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_absolute_path(char **cmd, int *errorflag)
{
	char	*path;

	path = cmd[0];
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	else
	{
		*errorflag = 127;
		ft_putstr_fd(FILE_OR_DIR, 2);
		ft_putendl_fd(path, 2);
		return (NULL);
	}
}

static char	*find_path_helper(t_data *data, char **cmd, int *errorflag)
{
	int		i;
	char	*path;
	char	*path_helper;

	i = 0;
	while (data->envp[i] != NULL)
	{
		path_helper = ft_strjoin(data->envp[i], "/");
		path = ft_strjoin(path_helper, cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		free (path_helper);
		free (path);
		i++;
	}
	if (!data->envp[i])
	{
		*errorflag = 127;
		ft_putstr_fd(CMD, 2);
		ft_putendl_fd(cmd[0], 2);
		return (NULL);
	}
	free (path_helper);
	return (path);
}

char	*find_path(t_data *data, char **cmd, int *errorflag)
{
	if (ft_strchr(cmd[0], '/'))
		return (find_absolute_path(cmd, errorflag));
	if (!data->envp_set)
	{
		*errorflag = 127;
		ft_putstr_fd(CMD, 2);
		ft_putendl_fd(cmd[0], 2);
		return (NULL);
	}
	return (find_path_helper(data, cmd, errorflag));
}

char	**set_cmd(char *av, int *errorflag)
{
	char	**cmd;
	int		error;

	error = 0;
	cmd = ft_pipex_split(av, ' ', &error);
	if (!cmd && error)
	{
		*errorflag = 1;
		ft_putstr_fd(MALLOC, 2);
	}
	else if (!cmd[0] && av[0] == '\0')
	{
		*errorflag = 126;
		ft_putendl_fd(PERMISSION, 2);
	}
	else if (!cmd[0])
	{
		*errorflag = 127;
		ft_putendl_fd(CMD, 2);
	}
	return (cmd);
}
