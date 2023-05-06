#include "RLEList.h"
#include "stdlib.h"
#define EMPTY_LIST -1

typedef struct node
{
    char value;
    int frequency;
    struct node* next;
}*Node;

struct RLEList_t{
    Node head;
};

RLEList RLEListCreate()
{
    RLEList newList = malloc(sizeof(*newList));
    if(newList)
        newList->head = NULL;
    return newList;
}

void RLEListDestroy(RLEList list)
{
    Node head = list->head, temp;
    while(head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(list);
}

bool checkAndMergeNeighbors(Node node)
{
    if(node == NULL || node->next == NULL)
        return false;
    if(node->value != node->next->value)
    {
        if(node->next->frequency)
        {
            return false;
        }
    }
    node->frequency += node->next->frequency;
    Node temp = node->next;
    node->next = temp->next;
    free(temp);
    return true;
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    //we can't add 2 same letters next to each other,
    //check the last node, if it has same value, we add the frequency.
    //else, we add a new node with frequency 1
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    Node newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
        return RLE_LIST_OUT_OF_MEMORY;
    newNode->value = value;
    newNode->frequency = 1;
    newNode->next = NULL;
    
    Node head = list->head;
    Node last = NULL;
    
    while(head != NULL)
    {
        last = head;
        head = head->next;
    }
    
    if(last == NULL)
        list->head = newNode;
    else
        last->next = newNode;
        
    checkAndMergeNeighbors(last);
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
        return -1;
    int size = 0;
    for(Node head = list->head; head ; head = head->next)
    {
        size += head->frequency;
    }
    return size;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    if(index < 0)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    int length = 0;
    Node head = list->head;
    Node prev = NULL;
    for(; head ; head = head->next)
    {
        length += head->frequency;
        if(index < length)
        {
            head->frequency -= 1;
            if(head->frequency== 0)
            {
                if(prev == NULL) //the head
                {
                    Node temp = head;
                    list->head = temp->next;
                    free(temp);
                }
                else
                {
                     //if after deletion we have 2 same value neighbor nodes, we merge them. 
                    checkAndMergeNeighbors(prev); //this one will remove the empty node.
                    checkAndMergeNeighbors(prev); //this one will merge two neighbors afte removal, if they're the same
                }
            }
            return RLE_LIST_SUCCESS;
        }
        prev = head;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{ 
    int saveResult = result != NULL;
    if(list == NULL)
    {
        if(saveResult)
                *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index < 0)
    {
        if(saveResult)
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    int length = 0;
    Node head = list->head;
    for(; head ; head = head->next)
    {
        length += head->frequency;
        if(index < length)
        {
            if(saveResult)
                *result = RLE_LIST_SUCCESS;
            return head->value;
        }
    }
    if(saveResult)
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    return 0;
}

int getNodeLength(Node node)
{
    if(node == NULL)
        return 0;
    int length = 0;
    for(int frequency = node->frequency; frequency; frequency /= 10, ++length);
    return length + 2; // + 1 for the letter itself and new line \n
}

int calcListStringSize(RLEList list)
{
    if(list == NULL)
        return 0;
    int length = 0;
    Node head = list->head;
    while(head)
    {
        length += getNodeLength(head);
        head = head->next;
    }
    return length;
}

char* nodeToStr(Node node)
{
    int length = getNodeLength(node);
    char* str = malloc(sizeof(char) * (length + 1));
    if(str == NULL)
        return NULL;
    str[length] = 0;
    str[length - 1] = '\n';
    int frequency = node->frequency;
    int k = length - 2;
    while(k >= 1)
    {
        str[k--] = '0' + frequency % 10;
        frequency /= 10;
    }
    str[k] = node->value;
    return str;
}
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    
    int saveResult = result != NULL;
    if(list == NULL)
    {
        if(saveResult)
                *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    int strSize = calcListStringSize(list);
    char *str = malloc(sizeof(char) * (strSize + 1));
    if(str == NULL)
    {
        if(saveResult)
                *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    str[strSize] = 0;
    int k = 0;
    Node head = list->head;
    for(; head ; head = head->next)
    {
        char *freqStr = nodeToStr(head);
        if(freqStr == NULL)
        {
            if(saveResult)
                *result = RLE_LIST_OUT_OF_MEMORY;
            free(str);
            return NULL;
        }
        for(int i = 0; freqStr[i];i++)
            str[k++] = freqStr[i];
        free(freqStr);
    }
    
    
    if(saveResult)
        *result = RLE_LIST_SUCCESS;
    return str;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list == NULL || map_function == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    Node head = list->head;
    Node prev = NULL;
    for(; head ;)
    {
        head->value = map_function(head->value);
        if(prev != NULL)
        {
            Node next = head->next;
            if(checkAndMergeNeighbors(prev))
            {
                head = next;
            }   
            else
            {
                prev = head;
                head = head->next;
            }
        }
        else
        {
            prev = head;
            head = head->next;
        }
    }
    return RLE_LIST_SUCCESS;
}