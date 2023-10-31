#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024

void handle_error(int exit_code, const char *format, ...);

int main(int argc, char *argv[])
{
int fd_from, fd_to;
ssize_t bytes_read, bytes_written;
char buffer[BUFFER_SIZE];

if (argc != 3)
{
handle_error(97, "Usage: cp file_from file_to\n");
}

fd_from = open(argv[1], O_RDONLY);
if (fd_from == -1)
{
handle_error(98, "Error: Can't read from file %s\n", argv[1]);
}

fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664); /* rw-rw-r-- */
if (fd_to == -1)
{
handle_error(99, "Error: Can't write to file %s\n", argv[2]);
}

while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
{
bytes_written = write(fd_to, buffer, bytes_read);
if (bytes_written == -1)
{
handle_error(99, "Error: Can't write to file %s\n", argv[2]);
}
}

if (bytes_read == -1)
{
handle_error(98, "Error: Can't read from file %s\n", argv[1]);
}

if (close(fd_from) == -1 || close(fd_to) == -1)
{
handle_error(100, "Error: Can't close file descriptor\n");
}

return (0);
}

void handle_error(int exit_code, const char *format, ...)
{
va_list args;
va_start(args, format);
vfprintf(stderr, format, args);
va_end(args);
exit(exit_code);
}
