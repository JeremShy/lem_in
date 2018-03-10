#include <lem_in.h>

void	print_error_and_exit(int nbr)
{
	perror("lem_in");
	write(1, "ERROR\n", sizeof("ERROR\n") - 1);
	exit(nbr);
}

void	print_and_exit(int nbr)
{
	write(1, "ERROR\n", sizeof("ERROR\n") - 1);
	exit(nbr);
}

void	free_dtab(char	**tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

size_t	count_dtab_len(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}
