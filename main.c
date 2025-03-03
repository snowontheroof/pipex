/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:59:47 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 16:45:11 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_envp_paths(t_data *data, char **envp)
{
	int		i;
	int		error;
	char	*path;

	i = 0;
	error = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_substr(envp[i], 5, (ft_strlen(envp[i]) - 5));
			break ;
		}
		i++;
	}
	if (!path)
		return ;
	data->envp = ft_split(path, ':', &error);
	if (!data->envp && error)
		exit_prog(data, 1, MALLOC);
	free (path);
	data->envp_set = 1;
}

static void	pipex(t_data *data, char **av, char **envp)
{
	set_envp_paths(data, envp);
	if (pipe(data->p) < 0)
		exit_prog(data, 1, NULL);
	data->pid1 = fork();
	if (data->pid1 < 0)
		exit_prog(data, 1, NULL);
	if (data->pid1 == 0)
		child1_process(data, envp, av[1], av[2]);
	parent_process(data, envp, av[4], av[3]);
}

static void	initialize_struct(t_data *data)
{
	data->envp = NULL;
	data->envp_set = 0;
	data->p[0] = -1;
	data->p[1] = -1;
	data->pid1 = -1;
	data->pid2 = -1;
	data->fd1 = -1;
	data->fd2 = -1;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->errorflag1 = 0;
	data->errorflag2 = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
	{
		ft_putendl_fd(AC, 2);
		return (1);
	}
	initialize_struct(&data);
	pipex(&data, av, envp);
	return (1);
}
