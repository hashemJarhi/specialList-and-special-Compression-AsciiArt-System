
#include "AsciiArtTool.h"
#define CHRODEL '@'
#define SPACE ' '

char mapFunction(char ch)
{
    if(ch == CHRODEL)
        return SPACE;
    if(ch == SPACE)
        return CHRODEL;
    return ch;
}

int main(int argc, char** argv) {
	if(argc != 4)
	{
	    return 0;
	}
	char *flag = argv[1];
	char *input = argv[2];
	char *output = argv[3];
	FILE *input_file = fopen(input, "r");
	if(input_file == NULL)
	    return 0;
	RLEList list = asciiArtRead(input_file);
	if(list == NULL)
	    return 0;
	FILE *output_file = fopen(output, "w");
	if(flag[1] == 'e')
	{
	    //print encoded
	    asciiArtPrintEncoded(list, output_file);
	}
	else //-i
	{
	    //print inverte
	    RLEListMap(list, mapFunction);
	    asciiArtPrint(list, output_file);
	}
	fclose(input_file);//closing file we have opened
	fclose(output_file);
	RLEListDestroy(list);
	
	return 0;
}   