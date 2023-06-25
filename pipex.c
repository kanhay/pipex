/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:52:39 by khanhayf          #+#    #+#             */
/*   Updated: 2023/06/25 14:09:41 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*exec_path(char *av, char	**paths_tab)
{
	char	**cmd;
	int		i;
	char	*xec_path;

	if (!av[2] || !av[3])
		ft_perror("permission denied");
	cmd = ft_split(av, ' ');
	i = 0;
	while (paths_tab[i])
	{
		xec_path = ft_strjoin(paths_tab[i], "/", cmd[0]);
		if (access(xec_path, X_OK) == 0)
		{
			release(cmd);
			release (paths_tab);
			return (xec_path);
		}
		else
			free (xec_path);
		i++;
	}
	return (NULL);
}

char	**get_cmds_paths(char **envp, char **av, t_pipex p)
{
	int		i;
	int		j;
	char	*paths;
	char	**paths_tab;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = envp[i];
		i++;
	}
	paths = paths + 5;
	p.cmds_paths = malloc(sizeof(char *) * 3);
	i = 0;
	j = 2;
	while (j < 4)
	{
		paths_tab = ft_split(paths, ':');
		p.cmds_paths[i++] = exec_path(av[j++], paths_tab);
	}
	p.cmds_paths[i] = NULL;
	return (p.cmds_paths);
}

void	childs(int i, t_pipex p, char **av, char **envp)
{
	char	**cmd_tab;

	cmd_tab = ft_split(av[i], ' ');
	if (i == 2)
	{
		dup2(p.infile_fd, 0);
		close(p.infile_fd);
		close(p.pipe_end[0]);
		dup2(p.pipe_end[1], 1);
		close(p.pipe_end[1]);
		execve(p.cmds_paths[0], cmd_tab, envp);
	}
	else if (i == 3)
	{
		dup2(p.pipe_end[0], 0);
		close(p.pipe_end[0]);
		close(p.pipe_end[1]);
		dup2(p.outfile_fd, 1);
		execve(p.cmds_paths[1], cmd_tab, envp);
	}
}

void	exec_cmds(t_pipex p, char **av, char **envp)
{
	int		status;
	pid_t	pid;

	if (pipe(p.pipe_end) < 0)
		ft_perror("pipe fails");
	pid = (fork());
	if (pid < 0)
		ft_perror("the creation of the 1st child process was unsuccessful");
	else if (pid == 0)
		childs(2, p, av, envp);
	pid = (fork());
	if (pid < 0)
		ft_perror("the creation of the 2nd child process was unsuccessful");
	else if (pid == 0)
		childs(3, p, av, envp);
	close(p.pipe_end[0]);
	close(p.pipe_end[1]);
	waitpid(-1, &status, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	if (!envp[0])
		ft_perror("No envp!");
	if (ac != 5)
		ft_perror ("the number of arguments is not 5");
	p.infile_fd = open(av[1], O_RDONLY, 0777);
	if (p.infile_fd < 0)
		ft_perror("the openning of the infile was unsuccessful");
	p.outfile_fd = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (p.outfile_fd < 0)
		ft_perror("the openning of the outfile was unsuccessful");
	p.cmds_paths = get_cmds_paths(envp, av, p);
	exec_cmds(p, av, envp);
	release (p.cmds_paths);
	return (0);
}
