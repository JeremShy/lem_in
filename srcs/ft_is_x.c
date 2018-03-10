#include <lem_in.h>

int8_t	is_command(char *ptr)
{
	if (ft_strncmp(ptr, "##start", 7) == 0)
		return (1);
	if (ft_strncmp(ptr, "##end", 5) == 0)
		return (2);
	return (0);
}

int8_t	is_nombre_entier(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
