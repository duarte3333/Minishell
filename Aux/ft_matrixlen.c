#include "../minishell.h"

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix[i][0] != 3)
		i++;
	return (i);
}
