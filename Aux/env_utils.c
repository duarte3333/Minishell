/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:31:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 20:41:06 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao retorno o ultimo elemento de uma lista do tipo t_env */
t_env	*ft_envlast(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/* Adiciona um novo elemento a uma lista t_env */
void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_envlast(*lst);
			ft_envlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

/* Cria um novo node para uma lista do tipo t_env */
t_env	*ft_envnew(char *str)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = str;
	return (new);
}

/* Liberta toda a memoria de uma lista do tipo do t_env */
int	ft_free_env(t_env **lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	return (1);
}

/* Esta funcao faz o ponteiro da lista voltar a apontar para a cabeca */
void	env_go_head(t_env **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}
