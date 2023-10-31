#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);


#define ELF_MAGIC_NUMBER_0 127
#define ELF_MAGIC_NUMBER_1 'E'
#define ELF_MAGIC_NUMBER_2 'L'
#define ELF_MAGIC_NUMBER_3 'F'


/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * Return: 0 on success, non-zero on error.
 *
 * This function is the entry point of the program. It processes command-line
 * arguments, opens a file, and performs operations on it.
 */
int main(int argc, char *argv[])
{
Elf64_Ehdr *header;
int fd;

if (argc != 2)
{
fprintf(stderr, "Usage: %s <ELF_file>\n", argv[0]);
exit(1);
}

fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
perror("Error: Can't open the file");
exit(2);
}

header = malloc(sizeof(Elf64_Ehdr));
if (header == NULL)
{
perror("Error: Memory allocation failed");
close(fd);
exit(2);
}

if (read(fd, header, sizeof(Elf64_Ehdr)) == -1)
{
perror("Error: Can't read the file");
free(header);
close(fd);
exit(3);
}

check_elf(header->e_ident);


free(header);
close_elf(fd);
return (0);
}
