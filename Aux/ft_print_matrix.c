#include "../minishell.h"

void ft_print_matrix(char **array)
{
    if (array == NULL)
        return;

    while (*array != NULL)
    {
        printf("%s\n", *array);
        array++;
    }
}