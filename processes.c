/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:00:27 by sojala            #+#    #+#             */
/*   Updated: 2025/02/20 14:40:38 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_data *data, char **envp, char *file, char *cmd)
{
	char	*path;

	close (data->p[0]);
	data->p[0] = -1;
	open_infile(data, file);
	data->cmd1 = set_cmd(cmd, &data->errorflag1);
	if (data->errorflag1)
		exit_prog(data, data->errorflag1, "");
	path = find_path(data, data->cmd1, &data->errorflag1);
	if (!path)
		exit_prog(data, data->errorflag1, "");
	if (dup2(data->p[1], STDOUT_FILENO) < 0)
		exit_prog(data, 1, NULL);
	if (dup2(data->fd1, STDIN_FILENO) < 0)
		exit_prog(data, 1, NULL);
	close_fd(data);
	execve(path, data->cmd1, envp);
	exit_prog(data, 1, NULL);
}

void	child2_process(t_data *data, char **envp, char *file, char *cmd)
{
	char	*path;

	close (data->p[1]);
	data->p[1] = -1;
	set_outfile(data, file);
	data->cmd2 = set_cmd(cmd, &data->errorflag2);
	if (data->errorflag2)
		exit_prog(data, data->errorflag2, "");
	path = find_path(data, data->cmd2, &data->errorflag2);
	if (!path)
		exit_prog(data, data->errorflag2, "");
	if (dup2(data->p[0], STDIN_FILENO) < 0)
		exit_prog(data, 1, NULL);
	if (dup2(data->fd2, STDOUT_FILENO) < 0)
		exit_prog(data, 1, NULL);
	close_fd(data);
	execve(path, data->cmd2, envp);
	exit_prog(data, 1, NULL);
}

void	parent_process(t_data *data, char **envp, char *file, char *cmd)
{
	int	status;
	int	status_child2;
	int	processes;
	int	pid;

	status = 0;
	processes = 2;
	data->pid2 = fork();
	if (data->pid2 < 0)
		exit_prog(data, 1, NULL);
	if (data->pid2 == 0)
		child2_process(data, envp, file, cmd);
	close_fd(data);
	while (processes > 0)
	{
		pid = wait(&status);
		if (pid == data->pid2)
			status_child2 = status;
		processes--;
	}
	if (WIFEXITED(status_child2))
		exit_prog(data, WEXITSTATUS(status_child2), "");
	exit_prog(data, 1, NULL);
}
