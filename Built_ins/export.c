#include "../minishell.h"

void ft_modify_print_matrix(char **array)
{
    int	i;

	i = -1;
	if (!array)
        return;
    while (array[++i])
    {
		printf("declare -x ");
        printf("%s\n", array[i]);
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
	
	(void)env;
	if (!(*lst)->content[1])
	{
		char_env = ft_env_lst_to_arr(g_data.env);
		ft_bubble_sort(char_env, ft_matrixlen(char_env));
		ft_modify_print_matrix(char_env);
		ft_free_matrix(&char_env);
		return ;
	}
	str = ft_split((*lst)->content[1], '=');	
	lst_env_export = env_lst_search(str[0]);
	if (!lst_env_export && str[1])
		ft_envadd_back(&(g_data.env), ft_envnew(ft_strdup((*lst)->content[1])));
	if (lst_env_export)
	{
		if (str[1])
		{
			free(lst_env_export->content);
			lst_env_export->content = ft_strdup((*lst)->content[1]);
		}
	}
	ft_free_matrix(&str);
}