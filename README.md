## CSCI-435-Assignment-1

#I am running this on a Mac and had to download ImageMagick to be able to draw yellow boxes. I have this program seperated into three files:

- main.c: In charge of taking in input from the command line and matching the correspodning files (.xml and .png) as well as exporting the anotated pictures to an output folder

- annotatingPics.c/annotatingPics.h: In charge of using ImageMagick to create yellow, transparent boxes around the nodes from images based on bounds from parsed xml data

- parsingXML.c/parsingXML.h: In charge of parsing through xml data to find leaf nodes (with no children) and collecting data points about their bounds to be given to annotatingPics.c

# To compile, you must run the command

gcc -o main main.c parsingXML.c annotatingPics.c `pkg-config --cflags --libs MagickWand`

# and then run the executable with this command

./main Programming-Assignment-Data/
