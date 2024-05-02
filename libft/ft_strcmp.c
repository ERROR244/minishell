#include "libft.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	int d = 0;
	while((s2[i] != '\0' && s1[i] != '\0'))
		{
			if(s1[i] != s2[i])
				d = s1[i] - s2[i];
			i++;
		}
	return(d);
}
