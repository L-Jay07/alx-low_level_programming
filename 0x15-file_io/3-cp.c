#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"

int open_source_file(const char *filename);
int open_destination_file(const char *filename);
int copy_file_contents(int source_fd, int destination_fd);
int close_file(int fd);
/**
 * main - Entry point for the cp program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, or an error code on failure.
 */
int main(int argc, char *argv[])
{
int source_fd, destination_fd;
if (argc != 3)
{
dprintf(2, "Usage: %s file_from file_to\n", argv[0]);
return (97);
}
source_fd = open_source_file(argv[1]);
if (source_fd == -1)
return (98);
destination_fd = open_destination_file(argv[2]);
if (destination_fd == -1)
{
close_file(source_fd);
return (99);
}
if (copy_file_contents(source_fd, destination_fd) == -1)
{
close_file(source_fd);
close_file(destination_fd);
return (99);
}
if (close_file(source_fd) == -1 || close_file(destination_fd) == -1)
return (100);
return (0);
}
/**
 * open_source_file - Opens the source file for reading.
 * @filename: The name of the source file.
 *
 * Return: The file descriptor if successful, or -1 on failure.
 */
int open_source_file(const char *filename)
{
int fd = open(filename, O_RDONLY);
if (fd == -1)
dprintf(2, "Error: Can't read from file %s\n", filename);
return (fd);
}

/**
 * open_destination_file - Opens the destination file for writing.
 * @filename: The name of the destination file.
 *
 * Return: The file descriptor if successful, or -1 on failure.
 */
int open_destination_file(const char *filename)
{
int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
if (fd == -1)
dprintf(2, "Error: Can't write to %s\n", filename);
return (fd);
}

/**
 * copy_file_contents - Copies contents from one file descriptor to another.
 * @source_fd: The source file descriptor.
 * @destination_fd: The destination file descriptor.
 *
 * Return: 0 on success, or -1 on failure.
 */
int copy_file_contents(int source_fd, int destination_fd)
{
char buffer[1024];
ssize_t read_result, write_result;
while ((read_result = read(source_fd, buffer, sizeof(buffer))) > 0)
{
write_result = write(destination_fd, buffer, read_result);
if (write_result == -1)
return (-1);
}
if (read_result == -1)
return (-1);

return (0);
}

/**
 * close_file - Closes a file descriptor.
 * @fd: The file descriptor to close.
 *
 * Return: 0 on success, or -1 on failure.
 */
int close_file(int fd)
{
if (close(fd) == -1)
dprintf(2, "Error: Can't close fd %d\n", fd);
return (0);
}
