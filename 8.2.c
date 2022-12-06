#include <stdio.h>
#include <limits.h>

//--------------------------------------------
int largestFile(int argc, char *argv[]);
//--------------------------------------------

#define CAPACITY 1000

int main(int argc, char *argv[])
{
    int maxIndex = largestFile(argc, argv);

    if(maxIndex == -1)
        printf("The entered files doesn't exist!\n");
    else
        printf("The file that takes up the most bytes in memory is %s\n", argv[maxIndex]);

    return 0;
}
//--------------------------------------------
int largestFile(int argc, char *argv[])
{
    int fileSize[CAPACITY],
        nonExisting = 0;

    for(int i = 1; i < argc; ++i)
    {
        FILE *myFile = NULL;

        if((myFile = fopen(argv[i], "r")) == NULL)
        {
            printf("The file %s can't be opened!\n", argv[i]);
            fileSize[i] = 0;
            ++nonExisting;
        }
        else
        {
            fseek(myFile, 0, SEEK_END);
            fileSize[i] = ftell(myFile);
            fclose(myFile);
        }
        //printf("%s %d\n", argv[i], fileSize[i]);
    }

    if(nonExisting != argc)
    {
        int maxSize = INT_MIN,
            maxIndex = -1;

        for(int i = 0; i < argc; ++i)
        {
            if(maxSize < fileSize[i])
            {
                maxSize = fileSize[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }
    else
        return -1;
}
