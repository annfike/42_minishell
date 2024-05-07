# 42_minishell
!! Add folder libft to run

# Lexer 
Makes list of tokens from the prompt  
Inside each token: str, type, len  
Divides by cases: space quotes < > | \$     
( ```$``` is replacing here)

# Lexer_check
Open double quotes (replace $ inside)   
Join tokens if there was no space between them  
Delete spaces   
Check list of tokens for errors

# Parser
Makes list of commands from tokens (divides only by pipes)

# Execution
Takes command   
If it's builtin -> exec_builtin   
If not -> execve

## Example 1
### prompt: 
```
echo $SHELL hi"dear $USER" >file1
```
### tokens ```((*msh)->tokens)``` after ```int		lexer(t_msh **msh, char *line);```
| str           | type           | len  |
| ------------- |:-------------:| -----:|
| "echo"        | 4 (word)      |   4   |
| " "           | 1 (space)     |   1   |
| "/bin/bash"   | 4 (word)      |   9   |
| " "           | 1 (space)     |   1   |
| "hi"          | 4 (word)      |   2   |
| "dear $USER"  | 2 (quotes)    |   10  |
| " "           | 1 (space)     |   1   |
| ">"           | 5(redirection out)     |   1   |
| " "           | 1 (space)     |   1   |
| "file1"        | 4 (word)     |   5  |


### tokens after ```int		lexer_check(t_msh **msh);```: 
| str           | type           | len  |
| ------------- |:-------------:| -----:|
| "echo"        | 4 (word)      |   4   |
| "/bin/bash"   | 4 (word)      |   9   |
| "hidear anna" | 4 (word)      |   11  |
| ">"           | 5(redirection out)     |   1   |
| "file1"        | 4 (word)     |   5  |


### commands ```((*msh)->cmds)``` after ```void	parser(t_msh **msh);```:   

command 1:			
  -  **args=[echo, /bin/bash, hidear anna]
  -  *file=file1
  -  hdoc=null


## Example 2
### prompt: 
```
ls | grep mini
```  
### tokens ```((*msh)->tokens)```  after ```int		lexer(t_msh **msh, char *line);```
| str           | type           | len  |
| ------------- |:-------------:| -----:|
| "ls"          | 4 (word)      |   2   |
| " "           | 1 (space)     |   1   |
| "\|"           | 3 (pipe)      |   1   |
| " "           | 1 (space)     |   1   |
| "grep"        | 4 (word)      |   4   |
| " "           | 1 (space)     |   1   |
| "mini"        | 4 (word)      |   4  |


### tokens after ```int		lexer_check(t_msh **msh);```: 
| str           | type           | len  |
| ------------- |:-------------:| -----:|
| "ls"          | 4 (word)      |   2   |
| "\|"          | 3 (pipe)      |   1   |
| "grep"        | 4 (word)      |   4   |
| "mini"        | 4 (word)      |   4  |


### commands ```((*msh)->cmds)``` after ```void	parser(t_msh **msh);```:   
command 1:			
  -  **args=[ls]
  -  *file=null
  -  hdoc=null	

command 2:			
  -  **args=[grep, mini]
  -  *file=null
  -  hdoc=null
    

              
------------------------------------------------------------------------------------------
# PIPES
```
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
```

Things to improve in this version of minishell (in next life maybe :D):			
  -  tabs in prompt should behave differently
  -  unset a=1 shouldn't work
  -  env: 
     - "_=" should show last command
     - SHLVL should change with each level of minishell
     - after "export a" env shouldn't show "a" (but export shows)

