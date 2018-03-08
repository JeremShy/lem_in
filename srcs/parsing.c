#include <lem_in.h>

char	*get_input(int fd)
{
	char	buffer[BUFF_SIZE_LEM];
	int		r;
	char	*input;

	input = NULL;
	while ((r = read(fd, buffer, BUFF_SIZE_LEM - 1)) > 0)
	{
		buffer[r] = '\0';
		if (input == NULL)
			input = ft_strdup(buffer);
		else
			input = ft_strjoinaf1(input, buffer);
	}
	if (r == -1)
		print_error_and_exit(1);
	return (input);
}

void	state_machine(char *input, t_parse *parse_structure)
{
	t_state_function table[3];
	t_state	state;
	char	*ptr;

	ft_memcpy(&table, (t_state_function[]){&parse_ants, &parse_rooms, &parse_pipes}, sizeof(table));
	state = STATE_ANTS;
	ptr = input;
	while (ptr)
	{

		(*(table[state]))(&state, parse_structure, &ptr);
		if (parse_structure->error)
			print_and_exit(2);
	}
}

t_parse	parsing(void)
{
	t_parse parse_structure;
	char	*input;

	ft_bzero(&parse_structure, sizeof(parse_structure));
	parse_structure.start_room_id = -1;
	parse_structure.end_room_id = -1;
	input = get_input(0);

	state_machine(input, &parse_structure);
	return (parse_structure);
}
