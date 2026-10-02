#include <stdio.h>
#include <stdlib.h>
#include "huffmanCoding.c"

int main()
{
    printf("Huffman coding for compression..!\n");
    createMinHeap(900000);
    print("Enter the No. of characters: ");
    int noOfChars;
    struct CharArray
    {
        char cars[900000];
        int freq[900000];
    } chars;

    scanf("%d", &noOfChars);
    char character;
    int frequency;
    for(int i = 0; i < noOfChars; i++){
        printf("Enter the char and frequency: ");
        scanf("%c %d", character, frequency);
        createNode(character, frequency)
    }
    return 0;
}
