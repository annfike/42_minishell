/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmiasnik <dmiasnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:37:14 by dmiasnik          #+#    #+#             */
/*   Updated: 2024/05/06 11:40:15 by dmiasnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(SIGQUIT, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	else
		ft_putstr_fd("\n", 1);
}

static void	execdir8(char	*stop)
{
	char	*line;
	int		fd[2];

	if (!stop)
		return ;
	pipe(fd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, stop))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	dup_files(t_list *file_lst)
{
	t_file	*file;
	int		infd;

	while (file_lst)
	{
		file = file_lst->content;
		infd = 0;
		if (file->type == 5)
			infd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else if (file->type == 6)
			infd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->type == 7)
			infd = open(file->file, O_RDONLY, 700);
		if (infd == -1)
		{
			error(NULL, file->file, strerror(errno));
			exit(1);
		}
		if (file->type == 7)
			dup2(infd, STDIN_FILENO);
		else
			dup2(infd, STDOUT_FILENO);
		close(infd);
		file_lst = file_lst->next;
	}
}

void	dup_pipes(int i, int fd[2], int fdp[2], t_list *cmds)
{
	if (i != 0)
	{
		close(fdp[1]);
		dup2(fdp[0], STDIN_FILENO);
		close(fdp[0]);
	}
	if (((t_cmd *)cmds->content)->hdoc)
		execdir8(((t_cmd *)cmds->content)->hdoc);
	if (cmds->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	dup_files(((t_cmd *)cmds->content)->file);
}

void	exec_fork(int fd[2], int i, t_list *cmds, int pids[1000])
{
	int	j;

	j = i;
	if (j == 0)
		while (j < 1000)
			pids[j++] = 0;
	pipe(fd);
	pids[i] = fork();
	signal(SIGINT, &handle_sigint);
	if (((t_cmd *)cmds->content)->hdoc)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, &handle_sigint);
}
