/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:13 by sojala            #+#    #+#             */
/*   Updated: 2025/02/19 16:33:40 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# define AC "pipex: expected format ./pipex file1 cmd1 cmd2 file2"
# define MALLOC "pipex: memory allocation failure"
# define FILE_OR_DIR "pipex: no such file or directory: "
# define PERMISSION "pipex: permission denied: "
# define CMD "pipex: command not found: "

typedef struct s_data
{
	char	**envp;
	int		envp_set;
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;
	int		fd1;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	int		errorflag1;
	int		errorflag2;
}				t_data;

//parsing
char	**ft_pipex_split(char const *s, char c, int *error);
char	**ft_freearray(char **array, int j, int *error);
int		ft_checkquote(char const *s, int i);
int		ft_strings(char const *s, char c);

//processes
void	child1_process(t_data *data, char **envp, char *file, char *cmd);
void	child2_process(t_data *data, char **envp, char *file, char *cmd);
void	parent_process(t_data *data, char **envp, char *file, char *cmd);

//open files
void	open_infile(t_data *data, char *file);
void	set_outfile(t_data *data, char *file);

//utils
char	*find_path(t_data *data, char **cmd, int *errorflag);
char	**set_cmd(char *av, int *errorflag);

//exit program
void	close_fd(t_data *data);
void	exit_prog(t_data *data, int exit_status, char *msg);

#endif
