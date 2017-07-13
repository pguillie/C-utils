#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

void		display_string_array(char **array)
{
	struct winsize	w;
	char			space[1024];
	size_t			array_dim[2];
	size_t			size;
	size_t			len;
	size_t			col;
	size_t			i[3];

	if (!array)
		return ;
	size = 0;
	len = 1;
	col = 0;
	memset(i, 0, 3 * sizeof(size_t));
	memset(space, ' ', 1024);
	if (ioctl(0, TIOCGWINSZ, &w) < 0)
	{
		while (array[size])
		{
			write(1, array[size], strlen(array[size]));
			write(1, "\n", 1);
			size++;
		}
	}
	else
	{
		while (array[size])
		{
			if (strlen(array[size]) + 1 > len)
				len = strlen(array[size]) + 1;
			size++;
		}
		array_dim[1] = w.ws_col / len ? (size - 1) / (w.ws_col / len) + 1 : size;
		array_dim[0] = (size - 1) / array_dim[1] + 1;
		while (i[0] < size)
		{
			write(1, array[i[1]], strlen(array[i[1]]));
			if (col++ < array_dim[0] && i[1] + (size - 1) / array_dim[0] + 1 < size)
			{
				write(1, space, len - strlen(array[i[1]]));
				i[1] += (size - 1) / array_dim[0] + 1;
			}
			else
			{
				write(1, "\r\n", 2);
				i[1] = ++i[2];
				col = 1;
			}
			i[0]++;
		}
	}
}
