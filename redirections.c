/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:42 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/05 18:58:00 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta funcao verifica qual o caso de redirecao encontrada */
int	check_token(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, "<"))
		return (3);
	else if (!ft_strcmp(str, ">"))
		return (4);
	return (0);
}

void	invalid_fd(t_list *lst)
{
	if (lst->fd_master[0] == -1)
	{
		perror("");
		g_data.status = 1;
		lst->master_error[0] = 1;
	}
	if (lst->fd_master[1] == -1)
	{
		perror("");
		g_data.status = 1;
		lst->master_error[1] = 1;
	}
}

/* Esta funcao cria os files descriptors consoante o caso
de redirecao */
void	redirect(char **division, int *i, t_list *lst)
{
	int	option;

	option = check_token(division[*i]);
	if ((lst->fd_master[0] != -1 && lst->fd_master[1] != -1) || option == 1)
	{
		if (lst->fd_master[0] > 2 && (option == 1 || option == 3))
			close(lst->fd_master[0]);
		if (lst->fd_master[1] > 2 && (option == 2 || option == 4))
			close(lst->fd_master[1]);
		if (option == 2)
			lst->fd_master[1] = open(division[++(*i)], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (option == 1)
			lst->fd_master[0] = ft_here_doc(division[++(*i)]);
		else if (option == 3)
			lst->fd_master[0] = open(division[++(*i)], O_RDONLY, 0644);
		else if (option == 4)
			lst->fd_master[1] = open(division[++(*i)], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		free(division[(*i) - 1]);
		invalid_fd(lst);
	}
}

/* Esta funcao avalia cada token. 
 - Caso de encontre uma redirecao cria os file descriptors 
 - Caso encontre um comando ou um argumento coloca no content do node
 - Caso encontre um 3, finaliza o node e inicializa um novo 
 node na linked list */
void	redirection(t_list	*lst, char **division)
{
	int		i;
	int		j;
	t_list	*temp;

	i = -1;
	j = 0;
	temp = lst;
	delete_quotes(division);
	while (division && division[++i])
	{
		if (division[i][0] == 3)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_matrixlen(&division[i + 1])));
			if (temp->next)
				temp = temp->next;
			j = 0;
		}
		else if (check_token(division[i]))
			redirect(division, &i, temp);
		else
			temp->content[j++] = ft_strdup(division[i]);
		free(division[i]);
	}
}
