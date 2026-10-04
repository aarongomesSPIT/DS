#include <stdio.h>
#include <stdlib.h>
#include "huffmanCoding.c"

int main()
{
    printf("Huffman coding for compression..!\n");
    printf("Enter the No. of characters: ");
    int noOfChars;
    if (scanf("%d", &noOfChars) != 1 || noOfChars < 1 || noOfChars > 100) {
        fprintf(stderr, "Enter a character count from 1 to 100.\n");
        return 1;
    }

    struct CharArray
    {
        char cars[100];
        int freq[100];
    } chars;

    int originalBits = 0;
    int compressedBits = 0;
    char character;
    for(int i = 0; i < noOfChars; i++){
        printf("Enter the char and frequency: ");
        if (scanf(" %c %d", &character, &chars.freq[i]) != 2 ||
            chars.freq[i] == 0) {
            fprintf(stderr, "Enter a character and a positive frequency.\n");
            return 1;
        }
        for (int previous = 0; previous < i; ++previous) {
            if (chars.cars[previous] == character) {
                fprintf(stderr, "Characters must be distinct.\n");
                return 1;
            }
        }
        chars.cars[i] = character;
    }

    struct MinHeapNode* root = buildHuffmanTree(chars.cars, chars.freq, noOfChars);

    printf("\nCharacter\tFrequency\tHuffman Code\tOriginal Bits\tCompressed Bits");
    int arr[MAX_TREE_HT];
    printCodes(root, arr, 0, &originalBits, &compressedBits);

    printf("\n\nTotal original bits: %d", originalBits);
    printf("\nTotal compressed bits: %d", compressedBits);
    printf("\nCompression ratio: %.2f:1",
           (double)originalBits / (double)compressedBits);
    printf("\nSpace saved: %.2f%%\n",
           100.0 * (double)(originalBits - compressedBits) /
               (double)originalBits);
    return 0;
}
