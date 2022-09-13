#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long get_file_size(FILE * fp);
unsigned char* bytes();
int main()
{
    char paht[50];
    printf("Enter file location: ");
    scanf("%s",&paht);
    FILE *fp = fopen(paht,"rb");
if (fp == NULL)
{
    printf("Failed opening file\n");
    return 1;
}
    long file_size = get_file_size(fp);
    unsigned char *Header = bytes();
    long header_size = sizeof(Header);
    long new_file_size = file_size + header_size; 
    unsigned char data[file_size];
    fread(data, 1, file_size, fp);
    fclose(fp);
    unsigned char new_data[new_file_size];
    for (int i = 0; i < header_size; i++)
    {
        new_data[i] = Header[i];
    }
    for (int i = 0; i < file_size; i++)
    {
        new_data[header_size++] = data[i];
    }
    FILE *copy = fopen("magicer-output","w");
    fwrite(new_data, 1, new_file_size, copy);
    fclose(copy);
    printf("Success! Output has been saved to current directory as 'magicer-output'\n");
  /*  for (int i = 0; i < new_file_size; i ++) {
            printf(" %X", new_data[i]);
        }
    printf("end");
  */
}
long get_file_size(FILE * fp)
{
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return file_size;
}
unsigned char* bytes()
{
    int exst;
//    unsigned char Header1[8];
//    unsigned char Header2[4];
    unsigned char *Header1 = (char*)calloc(8,sizeof(char));
    unsigned char *Header2 = (char*)calloc(4,sizeof(char));
    printf("Enter the format you wish to receive, '1' for PNG, '2' for JPG: ");
    scanf("%d",&exst);
    switch (exst)
    {
    case 1:
        memcpy(Header1, (unsigned char[]) { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A }, sizeof Header1);
        //Header1[8] ={0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
        return Header1;
        break;
    case 2:
        memcpy(Header2, (unsigned char[]) {0xFF, 0xD8, 0xFF, 0xE0 }, sizeof Header2);
        //Header2[4] = {0xFF, 0xD8, 0xFF, 0xE0};
        return Header2;
        break;
    default:
        printf("Format doesn't exist");
    }
}
