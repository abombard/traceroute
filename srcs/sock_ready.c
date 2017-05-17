/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_ready.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:36:32 by abombard          #+#    #+#             */
/*   Updated: 2017/05/17 16:36:34 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int		wsock_ready(int sfd)
{
	fd_set			fds;
	struct timeval	tv;
	int				nfds;

	FD_ZERO(&fds);
	FD_SET(sfd, &fds);
	tv.tv_sec = 1;
	tv.tv_usec = /* MAXWAIT */ 0;
	nfds = select(sfd + 1, NULL, &fds, NULL, &tv);
	return (nfds > 0);
}

int		rsock_ready(int sfd)
{
	fd_set			fds;
	struct timeval	tv;
	int				nfds;

	FD_ZERO(&fds);
	FD_SET(sfd, &fds);
	tv.tv_sec = 1;
	tv.tv_usec = /* MAXWAIT */ 0;
	nfds = select(sfd + 1, &fds, NULL, NULL, &tv);
	if (nfds < 0)
	{
		perror("select");
	}
	return (nfds > 0);
}
