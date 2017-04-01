#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# include "libft.h"

# include <sys/types.h>
# include <stdio.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <arpa/inet.h>

/* # define DEBUG */

# define PROGNAME			"ft_traceroute"

# define MAXADDRSIZE		64
# define DATALEN			(int)(sizeof(struct iphdr) + \
							sizeof(struct udphdr) + \
							sizeof(struct timeval))
# define MAXPACKET			4096

# define PORT	42

typedef struct	s_context
{
	char					hostname[MAXADDRSIZE];
	struct sockaddr_storage	sockaddr;
	socklen_t				sockaddrlen;
	int						sockfd;
	int						hops;
	int						req_per_hop;
	int						verbose;
}				t_context;

/*
** init
*/
void					usage(char *prog);
int						getopts(int argc, char **argv, t_context *context);

/*
** checksum
*/
u_int16_t				compute_checksum(u_int8_t *buf, unsigned int size);

/*
** traceroute
*/

#endif
