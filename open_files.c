/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:00 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 15:40:21 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_data *data, char *file)
{
	if (access(file, F_OK | R_OK) != 0)
	{
		data->errorflag1 = 1;
		if (access(file, F_OK) != 0)
			ft_putstr_fd(FILE_OR_DIR, 2);
		else
			ft_putstr_fd(PERMISSION, 2);
		ft_putendl_fd(file, 2);
	}
	else
	{
		data->fd1 = open(file, O_RDONLY);
		if (data->fd1 < 0)
		{
			data->errorflag1 = 1;
			perror("pipex");
		}
	}
}

void	set_outfile(t_data *data, char *file)
{
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		data->errorflag2 = 1;
		ft_putstr_fd(PERMISSION, 2);
		ft_putendl_fd(file, 2);
	}
	else
	{
		data->fd2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->fd2 < 0)
		{
			data->errorflag2 = 1;
			perror("pipex");
		}
	}
}
