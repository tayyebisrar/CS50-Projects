// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n"); // ensure file can be opened
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n"); // ensure file can be opened
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    if (fread(header, sizeof(BYTE), HEADER_SIZE, input) != 0)
    {
        fwrite(header, sizeof(BYTE), HEADER_SIZE, output);
    }
    else
    {
        return 1;
    }

    // Read samples from input file and write updated data to output file

    int16_t *current_samplebyte = malloc(sizeof(int16_t));
    while (fread(current_samplebyte, sizeof(int16_t), 1, input) != 0)
    {
        *current_samplebyte *= factor;
        fwrite(current_samplebyte, sizeof(int16_t), 1, output);
    }

    // Close files
    free(current_samplebyte);
    fclose(input);
    fclose(output);
}
