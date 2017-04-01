#include "traceroute.h"

u_int16_t	compute_checksum(u_int8_t *buf, unsigned int size)
{
	u_int64_t		sum;
	unsigned int	i;

	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += *(u_int16_t *)buf;
		buf += sizeof(u_int16_t);
		i += sizeof(u_int16_t);
	}
	if (size - i > 0)
		sum += *(u_int8_t *)buf;
	while ((sum >> 16) != 0)
		sum = (sum & 0xffff) + (sum >> 16);
	return ((u_int16_t)~sum);
}

int		checksum_isvalid(struct icmphdr *icmp)
{
	u_int16_t		checksum;
	u_int16_t		expected_checksum;

	checksum = icmp->checksum;
	icmp->checksum = 0;
	expected_checksum = compute_checksum((void *)icmp, sizeof(struct icmphdr));
	return (checksum == expected_checksum);
}
