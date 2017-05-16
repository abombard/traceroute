/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:00:48 by abombard          #+#    #+#             */
/*   Updated: 2017/05/06 15:00:50 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	usage(char *prog)
{
	fprintf(stderr, "Usage: %s [-h|-p <port>] ip\n", prog);
}
