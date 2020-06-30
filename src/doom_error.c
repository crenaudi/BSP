#include "../include/bsp.h"

void	doom_error(t_engine *e, unsigned int err, char *line)
{
	char			*s[4];
	unsigned int	close;

	s[0] = "Error malloc : ";
	s[1] = "Invalid map : ";
	s[2] = "Error texture : ";
	s[3] = "Error base_pal : ";
	close = err >> 16;
	ft_putstr(s[err ^ (1 << 16)]);
	if (line != NULL)
		ft_putendl(line);
	if (close == 1)
		close_engine(e);
}
