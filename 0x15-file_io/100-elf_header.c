#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_error(char *msg)
{
dprintf(STDERR_FILENO, "%s\n", msg);
exit(98);
}

void print_elf_header(Elf64_Ehdr *header)
{
printf("ELF Header:\n");
printf("  Magic:   ");
for (int i = 0; i < EI_NIDENT; i++)
{
printf("%02x ", header->e_ident[i]);
}
printf("\n");
printf("  Class:                             ");
if (header->e_ident[EI_CLASS] == ELFCLASS32)
{
printf("ELF32\n");
}
else if (header->e_ident[EI_CLASS] == ELFCLASS64)
{
printf("ELF64\n");
}
else
{
printf("<unknown: %x>\n", header->e_ident[EI_CLASS]);
}

printf("  Data:                              ");
if (header->e_ident[EI_DATA] == ELFDATA2LSB)
{
printf("2's complement, little endian\n");
}
else if (header->e_ident[EI_DATA] == ELFDATA2MSB)
{
printf("2's complement, big endian\n");
}
else
{
printf("<unknown: %x>\n", header->e_ident[EI_DATA]);
}

printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);

printf("  OS/ABI:                            ");
switch (header->e_ident[EI_OSABI])
{
case ELFOSABI_SYSV:
printf("UNIX - System V\n");
break;
case ELFOSABI_HPUX:
printf("UNIX - HP-UX\n");
break;
case ELFOSABI_STANDALONE:
printf("Standalone App\n");
break;
default:
printf("<unknown: %x>\n", header->e_ident[EI_OSABI]);
break;
}

printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);

printf("  Type:                              ");
switch (header->e_type)
{
case ET_REL:
printf("REL (Relocatable file)\n");
break;
case ET_EXEC:
printf("EXEC (Executable file)\n");
break;
case ET_DYN:
printf("DYN (Shared object file)\n");
break;
default:
printf("<unknown: %x>\n", header->e_type);
break;
}

printf("  Entry point address:               0x%lx\n", header->e_entry);
}

int main(int argc, char *argv[])
{
if (argc != 2)
{
print_error("Usage: elf_header elf_filename");
}

int fd;
if ((fd = open(argv[1], O_RDONLY)) == -1)
{
print_error("Error: Cannot open file");
}

Elf64_Ehdr header;
if (read(fd, &header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
{
print_error("Error: Cannot read ELF header");
}

if (header.e_ident[EI_MAG0] != ELFMAG0 ||
header.e_ident[EI_MAG1] != ELFMAG1 ||
header.e_ident[EI_MAG2] != ELFMAG2 ||
header.e_ident[EI_MAG3] != ELFMAG3) {
print_error("Error: Not an ELF file");
}

print_elf_header(&header);

close(fd);
return (0);
}
