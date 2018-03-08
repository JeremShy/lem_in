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
