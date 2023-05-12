/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/12 14:32:47 by mtiago-s         ###   ########.fr       */
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


typedef struct s_list
{
	char    		**content;
	char 			*path;
	int				fd[2];
	struct s_list	*next;
	struct s_list	*prev;
	int				(*ft_exec)(char **env, struct s_list *list);
}	t_list;

void	print_list(t_list *list);
//Aux functions
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(char *content, char **env);
t_list	*ft_lstlast(t_list *lst);
char	**ft_split(const char *str, char c);
void	*ft_calloc(size_t nelem, size_t elsize);
char	*ft_strjoin(char *s1, char const *s2);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *src);
void	ft_free_matrix(char ***m);
void 	delete_element(t_list **lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void 	go_head(t_list **lst);
void	ft_free_list(t_list **lst);

//Prompt
void 	prompt(char **env);

//Parse Function
void	parse(char *res, char *str, char sep, int slen);

//Getting the path
char	*get_path(char **env);
char	*get_cmd_path(char **env, char **cmd);

//Here doc
int		ft_here_doc(t_list *lst, int i);

//Redirections
int		redirection(t_list **lst);

//Execution
void 	execution(t_list *lst, char **env);

//Exec functions
int		check_token(char **str);
int 	__exec_out(char **env, t_list **lst);
int 	__exec_default(char **env, t_list **lst);
int 	__exec_here_doc(char **env, t_list **lst);
int 	__exec_in(char **env, t_list **lst);



#endif