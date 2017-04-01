#include "traceroute.h"
#include "libft.h"

#include <stdlib.h>

static char	ft_getopt(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	if (ft_strlen(arg) != 2)
		return (0);
	return (arg[1]);
}

static int	is_digit(char *arg)
{
	if (!arg)
		return (0);
	return (ft_atoi(arg));
}

int			getopts(int argc, char **argv, t_context *context)
{
	char	c;
	int		i;

	i = 1;
	while ((c = ft_getopt(argv[i])))
	{
		if (c == 'v')
			context->verbose = 1;
		else if (c == 't' && is_digit(argv[i + 1]) > 0)
		{
			context->hops = ft_atoi(argv[i + 1]);
			++i;
		}
		else
		{
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (i != argc - 1)
	{
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(context->hostname, argv[i], sizeof(context->hostname));
	return (0);
}
