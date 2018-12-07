/* C implementation QuickSort */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//Global Variables for testing
const int TESTS = 10; //Number of tests to run
const int N = 50000; //Length of Array(s) to sort

//Function to build Array of size elements
void buildArray(int *arr, int size)
{
	srand(0);
	for(int i = 0; i < size; i++)
	{
		arr[i] = rand() % 10;
	}
}

// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Function to average the timings data */
void avg(double times[])
{
  double sum = 0;
  for(int i = 0; i < TESTS; i++)
  {
    sum += times[i];
  }
  printf("Average Time: %f\n", sum / TESTS);
}

/* Function to print the arrays */
void printArray(double arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%f ", arr[i]);
	printf("\n");
}

// void printIntArray(int arr[], int size)
// {
// 	int i;
// 	for (i=0; i < size; i++)
// 		printf("%d ", arr[i]);
// 	printf("\n");
// }

// Driver program to test above functions
int main()
{
	printf("*****BEGINNING QUICKSORT TEST*****\n\n");

	double times[TESTS];
	printf("Testing Array Complete!\nSorting...\n");

	for(int i = 0; i < TESTS; i++)
	{
		int arr[N];
		buildArray(arr, N);
		// printf("Array #%d: ", i);
    // printIntArray(arr, N);
		printf("Array #%d Complete!\nSorting...\n", i);

		int n = sizeof(arr)/sizeof(arr[0]);
		clock_t start = clock();
		printf("Starting Ticks: %f\n", (double) start);

		quickSort(arr, 0, n-1);
		clock_t end = clock();
		printf("Ending Ticks: %f\n", (double) end);

		double totalTime = (double) (end - start) / CLOCKS_PER_SEC;
		// printf("SORTED Array #%d: ", i);
    // printIntArray(arr, N);
		printf("Array Sorted!\n");
		printf("Sort took: %f seconds\n\n", totalTime);
		times[i] = totalTime;
  }

	printf("Sort Timings: ");
	printArray(times, TESTS);
	avg(times);
	return 0;
}
