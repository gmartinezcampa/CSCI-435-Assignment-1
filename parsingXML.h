#ifndef PARSINGXML_H
#define PARSING_H

// Define a structure to hold the leaf element information
typedef struct {
    char id[64];
    int x; // Starting coordinates
    int y;
    int width; // Length and height of the boxes
    int height;
} LeafElement;

int extractInt(const char* str, const char* key);
int parseXML(const char *filename, LeafElement *elements, int maxElements);

#endif