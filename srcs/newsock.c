#include "traceroute.h"

struct addrinfo		*gethostaddressesinfo(
		const char *hostaddr, const int port)
{
	struct addrinfo	*results;
	struct addrinfo	hints;
	char			*portstr;
	int				err;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_RAW;
	hints.ai_flags = /* AI_CANONNAME */ 0;
	portstr = ft_itoa(port);
	if (!portstr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	err = getaddrinfo(hostaddr, NULL /* portstr */, &hints, &results);
	if (err)
	{
		fprintf(stderr, PROGNAME ": getaddrinfo: %s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}
	free(portstr);
	return (results);
}

static void			gethostaddrinfo(
		struct addrinfo *addresses,
		int *sndsfd,
		struct sockaddr *addr, socklen_t *addrlen)
{
	struct addrinfo		*rp;
	int					sfd;

	rp = addresses;
	while (rp != NULL)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd >= 0)
			break ;
		rp = rp->ai_next;
	}
	if (rp == NULL)
	{
		fprintf(stderr, PROGNAME ": failed to connect\n");
		exit(EXIT_FAILURE);
	}
	*sndsfd = sfd;
	ft_memcpy(addr, rp->ai_addr, rp->ai_addrlen);
	*addrlen = rp->ai_addrlen;
}

void	newsock(t_context *context)
{
	struct addrinfo		*addresses;

	addresses = gethostaddressesinfo(
			context->targetnamestr, context->port);
	gethostaddrinfo(addresses,
			&context->sndsfd,
			&context->targetaddr,
			&context->targetaddrlen);
	freeaddrinfo(addresses);
	gethostaddrstr(&context->targetaddr,
			context->targetaddrstr, sizeof(context->targetaddrstr));

	context->sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (context->sfd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in	from;

	ft_bzero(&from, sizeof(from));
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = htonl(INADDR_ANY);
	from.sin_port = 0;
	if (bind(context->sfd, (struct sockaddr *)&from, sizeof(from)))
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
}
