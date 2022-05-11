#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frameCount;
char strategy[7];
int * pages;
int pageCount = 0;
int sizeFrames = 0;

void pushBack(int frames[], int data);
void optimalStrategy(int pages[],int frameCount,int pageCount);
void fifoStrategy(int pages[],int frameCount,int pageCount);
void leastReacentlyUsedStrategy(int pages[],int frameCount,int pageCount);

int main()
{
    scanf("%d",&frameCount);
    scanf("%s",&strategy);

    pages = (int*) malloc(5000*sizeof(int));

    while(pages[pageCount-1] != -1)
    {
        scanf("%d", &pages[pageCount]);
        pageCount++;
    }

    if(strcasecmp(strategy,"OPTIMAL")==0)
        optimalStrategy(pages,frameCount,pageCount-1);
    else if(strcasecmp(strategy,"FIFO")==0)
        fifoStrategy(pages,frameCount,pageCount-1);
    else if(strcasecmp(strategy,"LRU")==0)
        leastReacentlyUsedStrategy(pages,frameCount,pageCount-1);

    return 0;
}

void pushBack(int frames[], int data){
frames[sizeFrames] = data;
sizeFrames++;
}

void optimalStrategy(int pages[],int frameCount,int pageCount)
{
    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    int frames[frameCount];
    for(int i=0; i<frameCount; i++)
        frames[i] = -1;
    int foundFlag;
    int replaceIndex = -1;
    int pageFaults = 0;

    for(int i=0; i<pageCount; i++)
    {
        printf("%02d",pages[i]);
        foundFlag=0;
        for(int j=0; j<frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                printf("     ");
                foundFlag=1;
                continue;
            }
        }

            if(foundFlag == 0)
            {
                if(frames[frameCount-1] != -1)
                printf(" F   ");
            else
                printf("     ");
                pageFaults++;
                if(frames[frameCount-1] == -1)
                        pushBack(frames, pages[i]);
                else
                {
                    int farFuture = i+1;
                    replaceIndex=-1;

                    for(int n=0; n<frameCount; n++)
                    {
                        int m;
                        for(m=i+1; m<pageCount; m++)
                        {
                            if(frames[n] == pages[m])
                            {
                                if(m > farFuture)
                                {
                                    farFuture = m;
                                    replaceIndex = n;
                                }
                                break;
                            }
                        }
                        if(m == pageCount)
                                replaceIndex = n;
                    }

                    if(replaceIndex == -1)
                            replaceIndex = 0;
                }
                frames[replaceIndex] = pages[i];
            }

            for(int m=0; m<frameCount; m++)
        {
            if(frames[m] != -1)
            printf("%02d ",frames[m]);
        }
        printf("\n");

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pageFaults-frameCount);
}

void fifoStrategy(int pages[],int frameCount,int pageCount)
{
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    int pageFaults = 0;
    int frames[frameCount];
    for(int i=0; i<frameCount; i++)
        frames[i] = -1;
    int foundFlag;

    for(int i=0; i<pageCount; i++)
    {
        printf("%02d",pages[i]);
        foundFlag=0;
        for(int j=0; j<frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                printf("     ");
                foundFlag=1;
                continue;
            }
        }

        if(foundFlag == 0)
        {
            if(frames[frameCount-1] != -1)
                printf(" F   ");
            else
                printf("     ");
            pageFaults++;
                if(frames[frameCount-1] == -1)
                        pushBack(frames, pages[i]);
                else
                    frames[(pageFaults-1)%frameCount]=pages[i];
        }

        for(int m=0; m<frameCount; m++)
        {
            if(frames[m] != -1)
            printf("%02d ",frames[m]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pageFaults-frameCount);
}

void leastReacentlyUsedStrategy(int pages[],int frameCount,int pageCount)
{
    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
   int pageFaults = 0;
   int frames[frameCount];
   for(int i=0; i<frameCount; i++)
        frames[i] = -1;
   int foundFlag;
   int countUse=0;
   int lru[pageCount];
   int replaceIndex;
   int fullFlag=1;

   for(int i=0; i<pageCount; i++)
   {
       printf("%02d",pages[i]);
       foundFlag=0;
       fullFlag=1;
       for(int j=0; j<frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                printf("     ");
                foundFlag=1;
                countUse++;
                lru[j]=countUse;
                continue;
            }
        }

        if(foundFlag == 0)
        {
            if(frames[frameCount-1] != -1)
                printf(" F   ");
            else
                printf("     ");
            pageFaults++;
            if(frames[frameCount-1] == -1)
                        {
                            pushBack(frames, pages[i]);
                            fullFlag=0;
                            countUse++;
                        }
            for(int m=0; m<frameCount; m++)
                  if(frames[m] == -1)
                        lru[m] = countUse;

                if(fullFlag == 1)
                    {
                        int lrused = lru[0];
                        replaceIndex=0;

                        for(int n=0; n<frameCount; n++)
                        {
                           if(lru[n] < lrused)
                           {
                               lrused = lru[n];
                               replaceIndex = n;
                           }
                        }
                        countUse++;
                        frames[replaceIndex] = pages[i];
                        lru[replaceIndex] = countUse;
                    }
        }
        for(int m=0; m<frameCount; m++)
        {
            if(frames[m] != -1)
            printf("%02d ",frames[m]);
        }
        printf("\n");
   }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pageFaults-frameCount);
}
