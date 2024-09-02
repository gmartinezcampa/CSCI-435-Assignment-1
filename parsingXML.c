// Name: Gisi Martinez-Campa
// Date: 9/2/2024
//
//
// This file is going to be used to parse through the XML to gather coordinates for each element in the screenshot

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsingXML.h"

// Helps extract nunbers from a string
int extractInt(const char* str, const char* key) {
    char *found = strstr(str, key);
    if (found) {
        // Converts numeric string to int
        return atoi(found + strlen(key) + 2);  // +2 to skip = and " characters
    }
    return -1; // Oop, no number here!
}

// Function to parse XML and extract leaf elements
int parseXML(const char *filename, LeafElement *elements, int maxElements) {
    FILE *xmlFile = fopen(filename, "r"); // Reading in the xml file
    if (!xmlFile) {
        printf("Failed to open XML file: %s\n", filename);
        return 0;
    }

    char line[256];
    int elementCount = 0;

    // Iterate through each line in file 
    while (fgets(line, sizeof(line), xmlFile)) {
        // Look for lines that represent a leaf element
        if (strstr(line, "<node") && strstr(line, "bounds") && elementCount < maxElements) {
            // Parse the bounds to extract coordinates and size
            char *bounds = strstr(line, "bounds=\"");
            if (bounds) {
                int x1, y1, x2, y2;
                sscanf(bounds, "bounds=\"[%d,%d][%d,%d]\"", &x1, &y1, &x2, &y2);
                
                // Checking if the node is a leaf (it should not have children)
                if (!strstr(line, "<node") || strstr(line, "</node>")) {
                    // This is a leaf node, store the details
                    elements[elementCount].x = x1;
                    elements[elementCount].y = y1;
                    elements[elementCount].width = x2 - x1;
                    elements[elementCount].height = y2 - y1;

                    // // Extract an ID or other attribute?
                    // char *idStart = strstr(line, "resource-id=\"");
                    // if (idStart) {
                    //     sscanf(idStart, "resource-id=\"%63[^\"]\"", elements[elementCount].id);
                    // } else {
                    //     strcpy(elements[elementCount].id, "unknown");
                    // }

                    elementCount++;
                }
            }
        }
    }

    fclose(xmlFile);
    return elementCount;
}
