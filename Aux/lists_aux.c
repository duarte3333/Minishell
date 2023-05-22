/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:16:16 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/19 16:29:05 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao cria um node, gerando logo o pipe para cada node*/
t_list	*ft_lstnew(int i)
{
	t_list	*new;

	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (NULL);
	new->content = ft_calloc(sizeof(char *), i + 1);
	new->fd_master[0] = 0;
	new->fd_master[1] = 1;
	if (pipe(new->fd) == -1)
		perror("");
	return (new);
}

//Esta funcao retorna o ultimo elemento de uma linked list
t_list	*ft_lstlast(t_list *lst)
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
void	ft_lstadd_back(t_list **lst, t_list *new)
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

/* Esta funcao manda a lista de volta para o node inicial */
void	go_head(t_list **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}
// void delete_element(t_list **lst)
// {
// 	t_list *temp;

// 	temp = (*lst);
//     if (lst && *lst)
//     {
// 		if ((*lst)->path)
// 			free((*lst)->path);
// 		if (!(*lst)->prev && !(*lst)->next)
// 			*lst = NULL;
// 		else if (!(*lst)->prev && (*lst)->next)
// 		{
// 			(*lst)->next->prev = NULL;
// 			*lst = (*lst)->next;
// 		}
// 		else if ((*lst)->prev && !(*lst)->next)
// 		{
// 			(*lst)->prev->next = NULL;
// 			*lst = (*lst)->prev;
// 		}
// 		else if ((*lst)->prev && (*lst)->next)
// 		{
// 			(*lst)->prev->next = (*lst)->next;
// 			(*lst)->next->prev = (*lst)->prev;
// 			*lst = (*lst)->prev;
// 		}
// 		//printf("[content] %s\n", (*lst)->content);
// 		if ((temp)->content)
// 			ft_free_matrix(&(temp->content));
// 		close(temp->fd[0]);
// 		close(temp->fd[1]);
// 		free(temp);
//     }
// }
