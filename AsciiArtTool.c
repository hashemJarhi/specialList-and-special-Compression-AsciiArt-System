#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdlib.h>

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream == NULL)
        return NULL;
    RLEList list = RLEListCreate();
    if(list == NULL)
        return NULL;
    char ch;
    while(fscanf(in_stream, "%c", &ch) != EOF)
    {
        if(RLEListAppend(list, ch) != RLE_LIST_SUCCESS)
        {
            RLEListDestroy(list);
            return NULL;
        }
    }
    return list;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    char *listToStr = RLEListExportToString(list, NULL);
    if(listToStr == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    int curr_ch_ind = 0;
    while(listToStr[curr_ch_ind])
    {
        char value = listToStr[curr_ch_ind++];
        int frequency = 0;
        for(; listToStr[curr_ch_ind] != '\n';curr_ch_ind++)
        {
            frequency *= 10;
            frequency += listToStr[curr_ch_ind] - '0';
        }
        for(int i = 0; i < frequency;i++)
            fprintf(out_stream, "%c", value);
        ++curr_ch_ind;
    } 
    free(listToStr);
    return RLE_LIST_SUCCESS;
}
 
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
     if(list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    char *listToStr = RLEListExportToString(list, NULL);
    if(listToStr == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
   
    fprintf(out_stream, "%s", listToStr);
    free(listToStr);
    return RLE_LIST_SUCCESS;
}

