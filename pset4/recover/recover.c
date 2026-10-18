#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *recoverfile = fopen(argv[1], "r");

    uint8_t buffer[512];
    int i = 0;
    bool first_jpeg = true;
    char filename[8];
    FILE *imagefile = NULL;

    while (fread(buffer, 1, 512, recoverfile) == 512)
    {
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 240) == 224)
        {
            if (!first_jpeg)
            {
                fclose(imagefile);
            }

            sprintf(filename, "%03i.jpg", i);
            imagefile = fopen(filename, "w");
            fwrite(buffer, 1, 512, imagefile);
            i++;
            first_jpeg = false;
        }

        else
        {
            if (!first_jpeg)
                fwrite(buffer, 1, 512, imagefile);
        }
    }
    fclose(imagefile);
    fclose(recoverfile);
}
