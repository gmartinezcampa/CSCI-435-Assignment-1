// Name: Gisi Martinez-Campa
// Date: 9/2/2024
//
// This project is the first programming assignment for CSCI 435.
// In this program, I will be using the ImageMagick API to create yellow, dashed boxes around the leaf components
// of a GUI (represented by a screenshot) by parsing information from a corresponding xml file.

#include "parsingXML.h"
#include "annotatingPics.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>



int main(int argc, char *argv[])
{
    // This will iterate through the xml and png files to find the corresponding pairs
    // Then call methods to parse xml files and annotate pictures
    DIR* dir;
    struct dirent* entry;
    char inputFile[128];
    char outputFile[128];
    char arrayFilePairs[10][2][128] = {{{'\0'}}};
    int fileIndex;
    char* lastDot;
    

    // Checking if proper # of arguments
    if (argc < 2) {
        printf("Not given the proper number of arguments. File: %s\n", argv[0]);
        return 1;
    }

    // Trying to open the directory
    dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Unable to open directory \n");
        return 1;
    }

    
    fileIndex = 0;
    char noExt[128];
    // Iterating over all files in directory to seperate pairs and extentions
    while ((entry = readdir(dir)) != NULL)
    {

        // Skip the `.` and `..` directories (don't need them) and hidden files (starting with `.`, like `.DS_Store`)
        if (entry->d_name[0] == '.') {
            continue;
        }

        snprintf(inputFile, sizeof(inputFile), "%s/%s", argv[1], entry->d_name); //This is the full file path
        int size = strlen(entry->d_name);
        if (size > 3) // Make sure it is long enough to take off the extention :P
        {
            strncpy(noExt, entry->d_name, size - 4);
            noExt[size - 4] = '\0'; // Don't want this running forever

            // // Check for the file extension
            // const char *ext = strrchr(entry->d_name, '.');
            // if (ext != NULL && (strcmp(ext, ".xml") == 0 || strcmp(ext, ".png") == 0)) 
            // {
            //     printf("inputFile: %s \n\n", inputFile);
            // } 
            // else 
            // {
            //     printf("inputFile (no ext): %s \n\n", inputFile);

            // }
        }
        else
        {
            continue;
        }

        for (int i = 0; i < 10; i++)
        {
            if (arrayFilePairs[i][0][0] == '\0') // Check if the first slot is empty
            {
                strncpy(arrayFilePairs[i][0], inputFile, sizeof(arrayFilePairs[i][0]));
                break;
            }
            else
            {
                char* temp = strstr(arrayFilePairs[i][0], noExt); // Check for the first occurrence of the filename without extension
                if (temp)
                {
                    if (arrayFilePairs[i][1][0] == '\0') // Check if the second slot is empty
                    {
                        strncpy(arrayFilePairs[i][1], inputFile, sizeof(arrayFilePairs[i][1]));
                        break;
                    }
                    else
                    {
                        printf("Something really weird happened in the for loop!. Check it out! \n");
                        // printf("arrayFilePairs[%d][1]: %s \n", i, inputFile);
                        // printf("noExt: %s\n\n", noExt);
                        break;
                    }
                }
            }
        }        
        fileIndex+=1; //make sure to go through all of the files in the directory
    }


    for (int i = 0; i < 10; i++)
    {
        if (arrayFilePairs[i][0][0] != '\0' && arrayFilePairs[i][1][0] != '\0') // Only get array elements with file names
        {
            // Printing to test if this works
            printf("Pair %d: %s, %s\n", i + 1, arrayFilePairs[i][0], arrayFilePairs[i][1]);

            char* xmlFile, *pngFile;

            if (strstr(arrayFilePairs[i][0], ".xml"))
            {
                xmlFile = arrayFilePairs[i][0];
                pngFile = arrayFilePairs[i][1];
            }
            else
            {
                xmlFile = arrayFilePairs[i][1];
                pngFile = arrayFilePairs[i][0];
            }

            // Parse XML and get leaf elements
            LeafElement elements[100]; // In theory, this will contain all the work aster calling parseXML
            int leafCount = parseXML(xmlFile, elements, 100);

            char noPNGExt[128];
            char* final;
            char com[] = "com";

            strncpy(noPNGExt, pngFile, strlen(pngFile) - 4);
            noPNGExt[strlen(pngFile) - 4] = '\0'; // Don't want this running forever
            
            final = strstr(noPNGExt, com);

            // Annotate the png file with yellow boxes
            snprintf(outputFile, sizeof(outputFile), "%s_output.png", final);
            annotateScreenshot(pngFile, outputFile, elements, leafCount);
        }
    }

    closedir(dir);


    return 0;
}