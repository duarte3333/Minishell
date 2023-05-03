/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:16:16 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/02/10 17:16:18 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

//Esta funcao cria um nó
t_lexer	*ft_lstnew(int i, t_tokens token, char *str)
{
	t_lexer	*new;

	new = (t_lexer *)ft_calloc(sizeof(t_lexer), 1);
	if (!new)
		return (NULL);
	new->i = i;
	new->token = token;
	new->str = str;
	return (new);
}

//Esta funcao retorna o ultimo elemento de uma linked list
t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//Esta funcao acrescenta um ultimo elemento na linked list
//Ou seja, coloca o last->next a apontar para o new
void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_lstlast(*lst);
			ft_lstlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}
