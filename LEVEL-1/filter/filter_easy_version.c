#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char*	buffer;
	char*	key;
	ssize_t bytes_read;
	int i, j;
	char c;
	size_t buffer_size;

	if (argc != 2 || *(argv[1]) == '\0') // verif argument
		return (1);

	buffer = malloc(sizeof(char) * 1); // alloc du buff, init a zero, et nullterm
	if (!buffer)
		return (perror("Error"), 1);
	buffer_size = 0;
	buffer[0] = '\0';

	key = argv[1]; // recup du password

	bytes_read = read(STDIN_FILENO, &c, 1); // lecture stdin jusqu'a EOF + rrealloc a chaque char
	while (bytes_read > 0)
	{
		char *tmp = realloc(buffer, buffer_size + 1);
		if (!tmp)
			return (perror("Error"), free(buffer), 1);
		buffer = tmp;
		buffer[buffer_size] = c;
		buffer_size++;
		bytes_read = read(STDIN_FILENO, &c, 1);
	}

	if (bytes_read < 0) // pour gerer erreurs de lecture
		return (perror("Error"), free(buffer), 1);

	if (bytes_read == 0) // remplacement du password
	{
		i = 0;
		j = 0;
		while (buffer[i])
		{
			// compare char by char entre buff et key
			while (buffer[i + j] == key[j] && buffer[i + j] && key[j])
				j++;
			if (key[j]) // si on a pas match tt le mot
				j = 0;
			
			if (j) // si on trouve la correspondance complete 
			{
				int k = 0;
				while (k < j)
				{
					printf("%c", '*');
					k++;
				}
				i += j; // pour skip les char remplaces 
				j = 0;
			}
			else // si pas de correspondance on affiche normalement
				printf("%c", buffer[i++]);
		}
	}
	free(buffer);
	return (0);
}