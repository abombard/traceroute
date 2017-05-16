#include "traceroute.h"

void	gethostnamestr(struct sockaddr *sockaddr,
			char *hostname, size_t size_max)
{
	struct sockaddr_in	*saddr;
	struct hostent		*he;

	if (sockaddr->sa_family != AF_INET)
	{
		fprintf(stderr, PROGNAME ": %s : sa_family not handled\n", __func__);
		exit(EXIT_FAILURE);
	}
	saddr = (struct sockaddr_in *)sockaddr;
	he = gethostbyaddr(&saddr->sin_addr, sizeof(saddr->sin_addr), sockaddr->sa_family);
	if (he)
		ft_strncpy(hostname, he->h_name, size_max);
	else
		gethostaddrstr(sockaddr, hostname, size_max);
}
