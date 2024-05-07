/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:03:37 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/06 12:16:56 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	fd[2]
pipe(fd);
fd[0] - из которого читаем
fd[1] - в который пишем
dup2(fd[1], 1); // перенаправляем стандартный вывод в файл


пример ls | grep
если встретили пайп( например флаг==1)
	pid = fork()

	если пид==0 (=дочка)
		dup2(fd[1], 1) подменяем реальный фд на фд пайпа, чтобы лс писал в фд пайпа
		close(fd[0]) закрываем fd[0] , так принято, он нам не нужен
		execve(cmds->content) выполняем команду
		close(fd[1])
	
	если пид!=0 (=родитель)
		dup2(fd[0], 0) подменяем реальный фд на фд пайпа ,чтобы греп читал из фд пайпа
		close(fd[1]) закрываем fd[1]
		waitpid(pid, NULL, 0) ждем завершения дочернего процесса
		close(fd[0]) закрываем fd[0]
*/

static void	exec_cmd(t_msh **msh, char **args, t_list *cmds)
{
	char	*cmd;
	char	**envs_arr;

	args = ((t_cmd *)(cmds->content))->args;
	if (!args[0])
		exit (0);
	if (exec_builtin(msh, args) != 0)
	{
		if (access(args[0], F_OK) == 0)
			cmd = args[0];
		else
			cmd = get_cmd_path((*msh)->envs, args[0]);
		if (cmd)
		{
			envs_arr = get_envs_arr(msh);
			execve(cmd, args, envs_arr);
			free(envs_arr);
			error(NULL, args[0], strerror(errno));
			exit(127);
		}
		error(NULL, args[0], "command not found");
		exit(127);
	}
	exit(EXIT_FAILURE);
}

static void	wait_pids(int i, int fdp[2], int pids[1000])
{
	int	j;
	int	ret;

	close(fdp[0]);
	close(fdp[1]);
	j = 0;
	while (j < i)
	{
		ret = 0;
		waitpid(pids[j], &ret, 0);
		g_sig = 0;
		g_sig = ret % 255;
		j++;
	}
}

static void	close_fd(int i, int fd[2], int fdp[2])
{
	if (i != 0)
	{
		close(fdp[0]);
		close(fdp[1]);
	}
	fdp[0] = fd[0];
	fdp[1] = fd[1];
}

int	execution(t_msh **msh, t_list *cmds)
{
	int		fdp[2];
	int		fd[2];
	int		i;
	int		onecom;
	int		pids[1000];

	i = 0;
	onecom = (cmds && !cmds->next && ((t_cmd *)cmds->content)->file == NULL);
	g_sig = 0;
	while (cmds)
	{
		if (onecom && ((t_cmd *)(cmds->content))->args &&
			((t_cmd *)(cmds->content))->args[0] && exec_builtin2(msh,
			((t_cmd *)(cmds->content))->args) == 0)
			break ;
		exec_fork(fd, i, cmds, pids);
		if (pids[i] == 0)
			dup_pipes(i, fd, fdp, cmds);
		if (pids[i] == 0)
			exec_cmd(msh, ((t_cmd *)(cmds->content))->args, cmds);
		close_fd(i++, fd, fdp);
		cmds = cmds->next;
	}
	wait_pids(i, fdp, pids);
	return (0);
}
