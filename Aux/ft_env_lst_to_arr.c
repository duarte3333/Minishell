#include "../minishell.h"

char **ft_env_lst_to_arr(t_env *lst_env)
{
    int size = ft_env_lstsize(lst_env);
    char **arr = (char **)malloc((size + 1) * sizeof(char *));
    if (!arr)
        return NULL;

    int i = 0;
    env_go_head(&lst_env);
    while (lst_env)
    {
        arr[i] = ft_strdup(lst_env->content);
        lst_env = lst_env->next;
        i++;
    }
    arr[size] = NULL;
    return arr;
}