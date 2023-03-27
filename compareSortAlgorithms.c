#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// allocate memory for the left and right side
	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));

	// traverse through n1 and n2
	for(i = 0; i < n1; i++)
	{
		L[i] = pData[l + i];
	}
	for(j = 0; j < n2; j++)
	{
		R[j] = pData[m + 1 + j];
	}

	// set variables equal to 0
	i = 0;
	j = 0;
	k = l;

	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			pData[k] = L[i];
			i++;
		}
		else
		{
			pData[k] = R[j];
			j++;
		}
		k++;
	}	
	while(i < n1)
	{
		pData[k] = L[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		pData[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}

void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int m  = (l + r) / 2;

		// send it through recursively
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);

		merge(pData, l, m, r);

		// allocated memory updated for merge function
		extraMemoryAllocated += (r - l + 1) * sizeof(int) / 4;
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int x, k, element;

	// traverse through loop
	for(x = 1; x < n; x++)
	{
		// set element equal to that of pData in this loop
		element = pData[x];

		for(k = x - 1; k >= 0; k--)
		{
			if(pData[k] > element)
			{
				// update
				pData[k + 1] = pData[k];
			}
			else
			{
				break;
			}
		}
		pData[k + 1] = element;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, x, tempVar;

	for(i = 0; i < n - 1; i++)
	{
		for(x = 0; x < n - i - 1; x++)
		{
			// after traversing, swap temp variables
			if(pData[x] > pData[x + 1])
			{
				tempVar = pData[x];
				pData[x] = pData[x + 1];
				pData[x + 1] = tempVar;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int r, y, min_index, tempVar;

	// traverse through one less than the original value in n
	for(r = 0; r < n - 1; r++)
	{
		min_index = r;

		for(y = r + 1; y < n; y++)
		{
			if(pData[y] < pData[min_index])
			{
				// update minimum index value
				min_index = y;
			}
		}
		tempVar = pData[r];
		pData[r] = pData[min_index];
		pData[min_index] = tempVar;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		if(*ppData)
		{
			for(int i = 0; i < dataSz; ++i)
			{
				fscanf(inFile, "%d\n", &((*ppData)[i]));
			}
		}
		// Implement parse data block
	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
