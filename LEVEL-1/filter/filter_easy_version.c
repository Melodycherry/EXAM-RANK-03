#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
char*buffer;
char*key;
ssize_t bytes_read;
int i, j;
char c;
size_t buffer_size;

if (argc != 2 || *(argv[1]) == '\0')
return (1);
buffer = malloc(sizeof(char) * 1);
if (!buffer)
return (perror("Error"), 1);
buffer_size = 0;
buffer[0] = '\0';
key = argv[1];
bytes_read = read(STDIN_FILENO, &c, 1);
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
if (bytes_read < 0)
return (perror("Error"), free(buffer), 1);
if (bytes_read == 0)
{
i = 0;
j = 0;
while (buffer[i])
{
while (buffer[i + j] == key[j] && buffer[i + j] && key[j])
j++;
if (key[j])
j = 0;
if (j)
{
int k = 0;
while (k < j)
{
printf("%c", '*');
k++;
}
i += j;
j = 0;
}
else
printf("%c", buffer[i++]);
}
}
free(buffer);
return (0);
}