
#include <stdio.h>
#include <stdlib.h>

void hexPrint(FILE* file) {
    int i = 0;
    unsigned char buffer;

    while (fread(&buffer, 1, 1, file)) {
        if (i % 16 == 0)
            printf("\n");
        printf("%-3u ", buffer);
        i++;
    }
}

void printChars(FILE* file) {
    int i = 0;
    unsigned char buffer;
    char stored = 0;

    while (fread(&buffer, 1, 1, file)) {

        if (buffer >= 0x20 && buffer <= 0x7e) {
            printf("%c", buffer);
        }
        if (buffer == 0x0d) {
            stored = buffer;
            continue;
        }
        if (stored == 0x0d && buffer == 0x0a) {
            printf("\n");
        }
        i++;
    }
}


int main(int argc, char* argv[])
{
    FILE* file;
    errno_t err;
    

    if (argc == 1 || argc > 3) {
        printf("Uso: PEReader.exe <executave.exe> [1-2], 1 - Hex Printing, 2 - Char Printing");
        return 0;
    }


    err = fopen_s(&file, argv[1], "rb");
    if (err == 0)
    {
        printf("Foi possivel ler os bytes do arquivo com sucesso. Codigo %d\n", err);
    }
    else
    {
        printf("Nao foi possivel ler os bytes do arquivo. Codigo %d\n", err);
    }

    if (file == NULL)
        printf("Não foi encontrado o arquivo fornecido.\n");


    if (argv[2]) {
        int value = atoi(argv[2]);
        printf("%u\n", value);
        switch (value) {
        case 1:
            hexPrint(file);
            break;
        case 2:
            printChars(file);
            break;

        }
    }

    fclose(file);

    return 0;
}

