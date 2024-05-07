/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:02:32 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/06 12:17:19 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	signal_handler(int signal)
{
	(void)signal;
	ft_putstr_fd(FT_PROMPT, 1);
	ft_putstr_fd(rl_line_buffer, 1);
	ft_putstr_fd("  ", 1);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (signal == SIGINT)
		g_sig = 1;
}

static void	execute(char *line, t_msh *msh)
{
	if (lexer(&msh, line) && lexer_check(&msh))
	{
		parser(&msh);
		execution(&msh, msh->cmds);
	}
	free_msh(&msh);
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;
	char	*line;

	(void)argc;
	(void)argv;
	msh = (t_msh *)malloc(sizeof(t_msh));
	parse_envs_create_list(&msh, envp);
	g_sig = 0;
	while (1)
	{
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline(FT_PROMPT);
		if (line == NULL)
			exit(1);
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		execute(line, msh);
	}
	free(msh);
	return (0);
}
/*
gcc minishell.c -lreadline -o minishell
make &&./minishell

leaks --atExit -- ./minishell
valgrind ./minishell
valgrind --leak-check=full ./minishell
valgrind --leak-check=full --show-leak-kinds=all ./minishell


https://github.com/kube/42homebrew

brew install readline
brew link --force readline
cpanm Term::ReadLine::Gnu
brew unlink readline
Check
brew info readline | head -1
*/