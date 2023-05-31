/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:36:36 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/31 19:05:27 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_modify_print_matrix(char **array)
{
    int	i;
	int j;
	int flag;

	i = -1;
	if (!array)
        return;
    while (array[++i])
    {
		printf("declare -x ");
		j = 0;
		flag = 0; 
		while (array[i][j])
		{
			printf("%c", array[i][j]);
			if (array[i][j] == '=' && !flag)
			{
				printf("\"");
				flag = 1;
			}
			j++;
		}
		printf("\"\n");
    }
}

void	ft_bubble_sort(char **arr, int size) 
{
    int 	i;
    int 	swapped;
    char	*temp;

	swapped = 1;
    while (swapped) 
	{
        swapped = 0;
        i = 0;
        while (i < size - 1) 
		{
            if (ft_strcmp(arr[i], arr[i + 1]) > 0) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
            i++;
        }
        size--;
    }
}

size_t	var_size(char *env_str)
{
	int i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	return (i);
}

t_env	*env_lst_search(char *input_var)
{
	t_env	*lst_env;
	
	lst_env = g_data.env;
	env_go_head(&lst_env);
	while (lst_env && lst_env->content)
	{
		lst_env = lst_env->next;
		if (!lst_env)
			break ;
		if (!ft_strncmp(lst_env->content, input_var, ft_strlen(input_var)) \
			&& var_size(lst_env->content) == ft_strlen(input_var))
			return (lst_env);
	}
	return (NULL);
}

void	__exec_export(char **env, t_list **lst)
{
	char	**str;
	t_env	*lst_env_export;
	char	**char_env;
	int		i;
	
	(void)env;
	if (!(*lst)->content[1])
	{
		char_env = ft_env_lst_to_arr(g_data.env);
		ft_bubble_sort(char_env, ft_matrixlen(char_env));
		ft_modify_print_matrix(char_env);
		ft_free_matrix(&char_env);
		return ;
	}
	i = 1;
	while ((*lst)->content[i])
	{
		str = ft_split((*lst)->content[i], '=');
		if ((*lst)->content[i][0] == '=' || !ft_str_islanum(str[0]) || ft_isdigit((*lst)->content[i][0]))
		{
			write(2, "minishell: export: \'", 21);
			write(2, ((*lst)->content[i]), ft_strlen((*lst)->content[i]));
			write(2, "\' not a valid identifier\n", 26);
			ft_free_matrix(&str);
			g_data.status = 1;
		}	
		else
		{
			lst_env_export = env_lst_search(str[0]);
			if (!lst_env_export)
				ft_envadd_back(&(g_data.env), ft_envnew(ft_strdup((*lst)->content[i])));
			if (lst_env_export)
			{
				if (str[1])
				{
					free(lst_env_export->content);
					lst_env_export->content = ft_strdup((*lst)->content[i]);
				}
			}
			ft_free_matrix(&str);
			g_data.status = 0;
		}
		i++;
	}
}