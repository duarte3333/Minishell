/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/23 17:58:23 by dsa-mora         ###   ########.fr       */
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
# include "Get_Next_Line/get_next_line.h"

struct global
{
	int			status;
	char		**env;
};

extern struct global g;

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
void	delete_element(t_list **lst);
void	go_head(t_list **lst);
void	ft_free_list(t_list **lst);
int		ft_matrixlen(char **matrix);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);


//Prompt
void	prompt(char **env);

//Parse Function
void	parse(char *res, char *str, char sep, int *array);

//Getting the path
char	*get_env(char **env, char *str);
char	*get_cmd_path(char **env, char **cmd);

//Here doc
int		ft_here_doc(char *str);

//Redirections
void	redirection(t_list	*pre_list, char **division);

//Execution
void	execution(t_list *lst, char **env);

//Exec functions
int		check_token(char *str);
void	__exec_default(char **env, t_list **lst);
void	__exec_pwd(char **env, t_list **lst);
void	__exec_cd(char **env, t_list **lst);
void	__exec_echo(char **env, t_list **lst);


#endif
