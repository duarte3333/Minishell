/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/30 16:12:12 by mtiago-s         ###   ########.fr       */
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
# include "Get_Next_Line/get_next_line.h"

typedef struct s_env
{
	char			*content;
	struct	s_env	*next;
	struct	s_env	*prev;
}	t_env;

struct global
{
	int			status;
	t_env		*env;
	char		**env_og;
};

extern struct global g_data;

typedef struct s_list
{
	char			**content;
	char			*path;
	int				fd_master[2];
	int				fd[2];
	struct s_list	*next;
	struct s_list	*prev;
	void			(*ft_exec)(char **env, struct s_list **list);
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
void 	ft_print_matrix(char **array);
char	*ft_replacement(char *str, char *s1, char *s2);

//Env utils
t_env	*ft_envnew(char *str);
t_env	*ft_envlast(t_env *lst);
void	ft_envadd_back(t_env **lst, t_env *new);
void	env_go_head(t_env **lst);
void	ft_free_env(t_env **lst);
char 	**ft_env_lst_to_arr(t_env *lst_env);
int		ft_env_lstsize(t_env *lst);
char	*search_env(char **env, char *str);

//Prompt
void	prompt(char **env);

//Parse Function
void	parse(char *res, char *str, char sep, int *array);

//Getting the path
char	*search_env(char **env, char *str);
char	*get_cmd_path(char **env, char **cmd);

//env
t_env	*get_env(char **env);
void	ft_free_env(t_env **lst);

//Here doc
int		ft_here_doc(char *str);

//Redirections
void	redirection(t_list	*pre_list, char **division);

//expander
char	**expander(char **divison, char **env);
char	*chg_dollar(char *input, char **env);

//Execution
void	execution(t_list *lst, char **env);

//Exec functions
void	close_fds(t_list **lst, int flag);
int		check_token(char *str);
void	__exec_default(char **env, t_list **lst);
void	__exec_pwd(char **env, t_list **lst);
void	__exec_cd(char **env, t_list **lst);
void	__exec_echo(char **env, t_list **lst);
void	__exec_env(char **env, t_list **lst);
void	__exec_exit(char **env, t_list **lst);
void	__exec_export(char **env, t_list **lst);
void	__exec_unset(char **env, t_list **lst);

//syntax
void	syntax_treatment(char *input);
void	delete_quotes(char **input, char c);

#endif
