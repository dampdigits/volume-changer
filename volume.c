/* Program: Volume modifies the volume of a .wav audio file.
   A .wav file consists of a 44 byte header followed by many audio samples of 2 byte each.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    uint8_t header[HEADER_SIZE];

    // Copying header from input file
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // Writing header from output file
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    int16_t sample;
    // Reading audio sample from input file
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // Updating audio sample
        sample *= factor;

        // Writing updated audio sample to output file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}