// Name: Gisi Martinez-Campa
// Date: 9/2/2024
//
// This project is the first programming assignment for CSCI 435.
// In this program, I will be using the ImageMagick API to create yellow, dashed boxes around the leaf components
// of a GUI (represented by a screenshot) by parsing information from a corresponding xml file.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <MagickWand/MagickWand.h>

int main(int argc, char *argv[])
{
    // This will iterate through the xml and png files to find the corresponding pairs
    // This will then change the

    MagickWand* wand;
    DrawingWand* drawingWand;
    PixelWand* pixelWand;
    DIR* dir;
    struct dirent* entry;
    struct stat st;
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
    char noExt[64];
    // Iterating over all files in directory to seperate pairs and extentions
    while ((entry = readdir(dir)) != NULL)
    {

        // Skip the `.` and `..` directories (don't need them) and hidden files (starting with `.`, like `.DS_Store`)
        if (entry->d_name[0] == '.') {
            continue;
        }

        // // Skip files that are too short to have a proper extension
        // int size = strlen(entry->d_name);
        // if (size <= 4) {
        //     continue;
        // }


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
        

        // if (fileIndex == 0)
        // {
        //     arrayFilePairs[0][0] = inputFile;
        //     fileIndex+=1
        //     break;
        // }
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

    // Printing to test if this workeds
    for(int i = 0; i < 9; i++) 
    {
        printf("Pair %d: %s, %s\n", i, arrayFilePairs[i][0], arrayFilePairs[i][1]);
    }

    // // Copy the file name to overflow safe variable (I think?)
    // strncpy(inputFile, argv[1], sizeof(inputFile) - 1);

    // // This will get the file name without the extension by finding last occurance of . (which should be before the extension)
    // lastDot = strrchr(inputFile, .);
    // if (lastDot != NULL)
    // {
    //     *lastDot = '\0';
    // }

    // // Finally, put the file name without the extention in OutputFile
    // snprintf(outputFile, sizeof(outputFile), "%s_output.png", inputFile)



    return 0;
}