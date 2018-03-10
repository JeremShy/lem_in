#include <lem_in.h>

int8_t	is_command(char *ptr)
{
	if (ft_strncmp(ptr, "##start", 7) == 0)
		return (1);
	if (ft_strncmp(ptr, "##end", 5) == 0)
		return (2);
	return (0);
}
