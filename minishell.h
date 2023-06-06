/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 18:55:59 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <term.h> 
# include <termios.h>
# include "Get_Next_Line/get_next_line.h"

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

struct s_global
{
	int				status;
	t_env			*env;
	int				hd;
	int				interrupted;
	struct termios	termios_save;
};

extern struct s_global	g_data;

typedef struct s_list
{
	char			**content;
	char			*path;
	int				fd_master[2];
	int				fd[2];
	int				master_error[2];
	struct s_list	*next;
	struct s_list	*prev;
	void			(*ft_exec)(struct s_list **list);
}	t_list;

void	print_list(t_list *list);

//Aux functions
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(int i);
t_list	*ft_lstlast(t_list *lst);
char	**ft_split(const char *str, char c);
void	*ft_calloc(size_t nelem, size_t elsize);
char	*ft_strjoin(char *s1, char const *s2);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *src);
void	ft_free_matrix(char ***m);
void	delete_element(void **lst);
void	go_head(t_list **lst);
void	ft_free_list(t_list **lst);
int		ft_matrixlen(char **matrix);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	**ft_matrixdup(char **matrix);
int		ft_atoi(const char *nptr);
void	ft_print_matrix(char **array);
char	*ft_replacement(char *str, char *s1, char *s2);
char	*ft_itoa(int nbr);
void	error_handle(char *cmd);
int		ft_isalnum(int i);
int		ft_str_islanum(char *str);
int		ft_isdigit(int i);
int		ft_lstsize(t_list *lst);
int		is_built_in(t_list *lst);
void	ft_bubble_sort(char **arr, int size);

//Syntax
void	syntax_treatment(char *input);
void	delete_quotes(char **input);
void	treat_quotes(char *input, int i, int *flag);
void	delete_quotes_string(char **input, char c);
void	syntax_error(char *str, char *input, int size);

//Env utils
t_env	*ft_envnew(char *str);
t_env	*ft_envlast(t_env *lst);
void	ft_envadd_back(t_env **lst, t_env *new);
void	env_go_head(t_env **lst);
void	ft_free_env(t_env **lst);
char	**ft_env_lst_to_arr(t_env *lst_env);
int		ft_env_lstsize(t_env *lst);
t_env	*env_lst_search(char *input_var);
char	*search_env(char **env, char *str);

//Prompt
void	prompt(void);

//Signals
void	signals_default(void);
void	signals_here_doc(int sign);
void	handle_sign(int sign);
void	handle_quit(int sign);

//Parse Function
void	parse(char *res, char *str, char sep, int *array);

//Getting the path
char	*search_env(char **env, char *str);
char	*get_cmd_path(char **env, char **cmd);

//Env
t_env	*get_env(char **env);
void	ft_free_env(t_env **lst);

//Here doc
int		ft_here_doc(char *str);

//Redirections
void	redirection(t_list	*pre_list, char **division);

//Expander
char	**expander(char **divison, char **env);
char	*chg_dollar(char *input, char **env);

//expander utils
int		is_alphnum(char c);
char	*prepare_string(char *str, int i, int size);
char	**prepare(char *str);

//Execution
void	execution(t_list *lst);

//Exec functions
void	close_fds(t_list **lst, int flag);
int		check_token(char *str);
void	__exec_default(t_list **lst);
void	__exec_pwd(t_list **lst);
void	__exec_cd(t_list **lst);
void	__exec_echo(t_list **lst);
void	__exec_env(t_list **lst);
void	__exec_exit(t_list **lst);
void	__exec_export(t_list **lst);
void	__exec_unset(t_list **lst);

#endif
