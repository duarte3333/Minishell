/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst_to_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:55:33 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 20:13:34 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao transforma uma lista do tipo t_env
num variavel do tipo char**. */
char	**ft_env_lst_to_arr(t_env *lst_env)
{
	int		size;
	char	**arr;
	int		i;

	arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	size = ft_env_lstsize(lst_env);
	i = 0;
	env_go_head(&lst_env);
	while (lst_env)
	{
		arr[i] = ft_strdup(lst_env->content);
		lst_env = lst_env->next;
		i++;
	}
	arr[size] = NULL;
	return (arr);
}
