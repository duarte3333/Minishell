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

#ifndef LEXER_H
# define LEXER_H

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


typedef enum s_tokens
{
	_WORD = 1,
	_PIPE = '|',
	_GREATER = '>',
	_LESSER = '<',
	_WHITESPACE = ' ',
	_AMPERSAND = '&',
	_BACKSLASH = '\\',
	_SEMICOLON = ';',
	_TAB = '\t',
	_NEWLINE = '\n',
	_NULL = 0,
	_QOUTE = '\'',
	_DQUOTE = '\"',
} t_tokens;

typedef struct s_lexer
{
	char    		*str;
	t_tokens   		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

size_t	ft_strlen(const char *str);
t_lexer	*ft_lstnew(int i, t_tokens token, char *str);
t_lexer	*ft_lstlast(t_lexer *lst);
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);



#endif
