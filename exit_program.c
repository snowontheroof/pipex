/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:59:38 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 16:31:42 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			free (array[i++]);
		free (array);
	}
}

void	close_fd(t_data *data)
{
	if (data->p[0] != -1)
	{
		close (data->p[0]);
		data->p[0] = -1;
	}
	if (data->p[1] != -1)
	{
		close (data->p[1]);
		data->p[1] = -1;
	}
	if (data->fd1 != -1)
	{
		close (data->fd1);
		data->fd1 = -1;
	}
	if (data->fd2 != -1)
	{
		close (data->fd2);
		data->fd2 = -1;
	}
}

void	exit_prog(t_data *data, int exit_status, char *msg)
{
	close_fd(data);
	free_array(data->envp);
	free_array(data->cmd1);
	free_array(data->cmd2);
	if (!msg)
		perror("pipex");
	else if (*msg)
		ft_putendl_fd(msg, 2);
	exit(exit_status);
}
