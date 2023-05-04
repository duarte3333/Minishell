/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/03 17:27:14 by mtiago-s         ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
	char    		**content;
	int				fd[2];
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

//Aux functions
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(char *content);
char	**ft_split(const char *str, char c);
void	*ft_calloc(size_t nelem, size_t elsize);
char	*ft_strjoinn(char *s1, char const *s2);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

//Parse Function
void	parse(char *res, char *str, char sep, int slen);





#endif
