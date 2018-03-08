#ifndef LEM_IN_H
# define LEM_IN_H

# include <ft_printf.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# define BUFF_SIZE_LEM 2

typedef enum e_state
{
	STATE_ANTS,
	STATE_ROOMS,
	STATE_PIPES
}	t_state;

typedef struct	s_room
{
	int64_t				id;
	int8_t				occupied;
	int8_t				*name;
	struct s_pipe		*pipes;
}				t_room;

typedef struct	s_pipe
{
	t_room			*cote1;
	t_room			*cote2;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_parse
{
	int8_t		error;
	t_room		*rooms;
	size_t		nbr_ants;
	size_t		nbr_rooms;
	int64_t		start_room_id;
	int64_t		end_room_id;
	size_t		nbr_ants_start;
	size_t		nbr_ants_end;
} 				t_parse;

typedef void (*t_state_function)(t_state *, t_parse *, char **);

t_parse	parsing(void);
void	print_error_and_exit(int	nbr);
void	print_and_exit(int	nbr);
void	parse_ants(t_state *, t_parse *, char **);
void	parse_rooms(t_state *state, t_parse *parse_structure, char **ptr);
void	parse_pipes(t_state *state, t_parse *parse_structure, char **ptr);

int8_t	is_command(char *ptr);


#endif
