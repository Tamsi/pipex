/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:31:14 by tbesson           #+#    #+#             */
/*   Updated: 2022/06/22 18:34:51 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char **cmd, char **envp)
{
	if (cmd[0] && get_cmd_path(cmd[0], envp))
	{
		execve(get_cmd_path(cmd[0], envp), cmd, envp);
		freetab(cmd);
	}
	else
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		freetab(cmd);
		exit(EXIT_FAILURE);
	}
}

static void	exec_first_cmd(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			return (perror(av[1]));
		cmd = ft_split(av[2], ' ');
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(cmd, envp);
	}
}

static void	exec_last_cmd(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd[1] < 0)
			return (perror(av[4]));
		cmd = ft_split(av[3], ' ');
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		exec_cmd(cmd, envp);
	}
}

static void	pipex(char **av, char **envp)
{
	int	pipefd[2];
	int	fd[2];
	int	status;

	if (pipe(pipefd) < 0)
		return (perror(NULL));
	exec_first_cmd(pipefd, fd, av, envp);
	exec_last_cmd(pipefd, fd, av, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 2);
		return (1);
	}
	pipex(av, envp);
	return (0);
}
