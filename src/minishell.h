/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelaloy <adelaloy <adelaloy@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:07:06 by adelaloy          #+#    #+#             */
/*   Updated: 2024/05/07 10:14:09 by adelaloy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include <errno.h>

# define FT_PROMPT "\033[0;35mmyshell\033[0m$ "

extern int	g_sig;

/*
lexer - разбивает строку на токены (кейсы: пробел, кавычки, $, |, >, <), 
подставляет энв вместо $, проверяет на ошибки
parser - создает лист команд с аргументами и тп 
(деление на команды только по пайпам)
execution - выполняет команды, ищет их либо в билдин либо в паф
		
types
1-space
2-quotes
3-pipe
4-word
5-redirection out 
6-redirection out double
7-redirection in 
8-redirection in double
*/

typedef struct s_token
{
	char	*str;
	int		type;
	int		len;
}	t_token;

/* структура для  редиректов внутри команды*/
typedef struct s_file
{
	char	*file;
	int		type;
}	t_file;

typedef struct s_cmd
{
	char	**args;
	t_list	*file;
	char	*hdoc;
}	t_cmd;

typedef struct s_msh
{
	t_list	*envs;
	t_list	*tokens;
	t_list	*cmds;
}	t_msh;

/* lexer */
int		lexer(t_msh **msh, char *line);
int		redirection(char *line, int *i, t_token *token);
int		word(char *line, int *i, t_token *token);
void	set_token_values(char *str, int type, int len, t_token *token);

/* lexer_dollar */
int		dollar(t_msh **msh, char *line, int *i, t_token *token);

/* lexer_quotes */
int		quotes(char *line, int *i, t_token *token);
int		double_quotes(char *line, int *i, t_token *token);

/* lexer_quotes_open */
int		open_quotes(t_msh **msh);

/* lexer_space_pipe */
int		ft_pipe(int *i, t_token *token);
int		space(int *i, t_token *token);
int		delete_spaces(t_msh **msh);

/* lexer_check */
int		lexer_check(t_msh **msh);

/* env */
int		parse_envs_create_list(t_msh **msh, char **envp);
void	print_envs(t_msh **msh);
char	*get_env_name(char *env);
char	*get_env_value(t_list *env, char *str);

/* parser */
void	parser(t_msh **msh);

/* execution */
int		execution(t_msh **msh, t_list *cmds);
char	*get_cmd_path(t_list *envs, char *cmd);
void	dup_files(t_list *file_lst);
void	dup_pipes(int i, int fd[2], int fdp[2], t_list *cmds);
void	exec_fork(int fd[2], int i, t_list *cmds, int pids[1000]);

/* builtin */
int		exec_builtin(t_msh **msh, char **args);
int		exec_builtin2(t_msh **msh, char **args);

/* builtin_exit*/
int		ft_exit(char **args);

/* builtin_echo_cd_pwd */
int		ft_echo(char **args);
void	set_new_dir_envs(t_msh **msh, char *dir_begin, char *dir_end);
int		ft_cd2(t_msh **msh, char **args);
int		ft_pwd(void);

/* builtin_export */
char	**ft_sort_str_arr(char **arr);
void	print_arr(char **arr);
char	**get_envs_arr(t_msh **msh);
void	export_no_args(t_msh **msh);
int		ft_export2(t_msh **msh, char **args);

/* builtin_export_args */
void	set_new_env_value(t_msh **msh, char *arg);
void	export_args(t_msh **msh, char *arg);

/* builtin_unset_env */
int		ft_unset2(t_msh **msh, char **args);
int		ft_env(t_msh **msh);

/* utils */
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lst_print(t_list *lst);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
void	print_tokens(t_msh **msh);
void	error(char *cmd, char *arg, char *error);

/* free*/
void	free_msh(t_msh **msh);

#endif