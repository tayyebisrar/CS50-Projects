#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE; // BYTE is more succinct

const int JPGSIZE = 512; // trying to avoid magic numbers

bool checkforheader(BYTE data[]);
void create_new_file(FILE **output, int *jpgc, char *filename);
void write_to_file(BYTE data[], FILE **output);

int main(int argc, char *argv[])
{
    if (argc != 2) // if number of arguments doesn't match
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r"); // open card.raw
    if (input == NULL)
    {
        printf("Error opening file.\n"); // if it doesn't open right say this
        return 1;
    }

    BYTE buffer[JPGSIZE]; // create array to hold each block of data

    int jpgc = -1; // variables (could've started with 0)
    bool is_new_jpg = false;
    char filename[8];
    FILE *output = fopen("000.jpg", "w"); // open first file

    while (fread(buffer, 1, JPGSIZE, input) == JPGSIZE)
    {
        is_new_jpg = checkforheader(buffer); // check for header file

        if (!is_new_jpg && jpgc == -1) // if the program just started, i.e. no header files yet
        {
            continue;
        }

        if (is_new_jpg) // once a header file is detected
        {
            create_new_file(&output, &jpgc, filename); // create new file
            is_new_jpg = false;                        // reset the detector
        }

        if (jpgc >= 0) // if the program just started this won't run
        {
            write_to_file(buffer, &output); // write to file
        }
    }

    fclose(input);
    fclose(output);
    return 0; // return if all is well
}

bool checkforheader(BYTE data[])
{
    BYTE header[3] = {0xff, 0xd8, 0xff}; // create header array for checking against
    for (int i = 0; i < 3; i++)
    {
        if (data[i] != header[i]) // if at any point it doesn't match
        {
            return false; // it's not a header
        }
    }
    if (!(data[3] >= 0xe0 &&
          data[3] <= 0xef)) // even if the first 3 match but the 4th doesn't start with 1110
    {
        return false; // it's not a header
    }
    return true; // if it wasn't detected as not being a header, it must be a header
}

void create_new_file(FILE **output, int *jpgc, char *filename) // create new file
{
    fclose(*output);                      // close the old file
    (*jpgc)++;                            // increment the counter
    sprintf(filename, "%03i.jpg", *jpgc); // modify the filename with the new count
    *output = fopen(filename, "w");       // open a new file with the updated filename
    return;
}

void write_to_file(BYTE data[], FILE **output)
{
    fwrite(data, 1, JPGSIZE, *output); // write the data to that file.
}
