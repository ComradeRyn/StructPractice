
// Created by AJ DiLeo
// For use in CS211 Spring 2024 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// ******STEP 0: SKIP TO MAIN FUNCTION*********

// TODO: Transform Array
// Input: 2D array, number of rows, number of cols
// For each row in the array, you will swap the first half of each row
// with its second half. For rows with an odd number, the middle
// element will stay in place
// e.g, input: 
// [
// 	[1, 2, 3, 4],
// 	[5, 6, 7, 8],
// 	[9, 10, 11, 12]
// ]
// now swap the first half of the rows with the second half
// [
// 	[3, 4, 1, 2],
// 	[7, 8, 5, 6],
// 	[11, 12, 9, 10]
// ]
// DONE!
void transformArray(int** arr, int rows, int cols) {
	int midPoint = cols/2;
	if(cols % 2 != 0){
		midPoint++;
	}
	for(int i = 0; i < rows; i++){
		int front = 0;
		for(int middle = midPoint; middle < cols; middle++){
		        int temp = arr[i][middle];
			arr[i][middle] =  arr[i][front];
			arr[i][front] = temp;
			front++;
		}
	}
	return;
}

typedef struct MusicRecord {
	int id;
	char* name;
	int releaseYear;
} record_t;

// We create a new C type called "record_t" which is of type struct
// with specific attributes
// It is a common naming convention to append
// a _t to a struct to denote that it is a new type

// TODO: Number of Duplicate Records
// Input array of records, total number of records
// Identify the total number of duplicates (if any)
// in the record collection. A duplicate is a record
// of the same title and release year.

// e.g., RecordA 1970, RecordB 1968, RecordA 1970, RecordC 1970
// there is a total of 1 duplicate 
int numDuplicates(record_t* records, int numRecords) {
	// RETURN the duplicate count (if there are any)
	// ELSE 0
	int count = 0;
	for(int i = 0; i < numRecords; i++){
		int ptr = 0;
		record_t currentRecord = records[i];
		while(ptr < i){ 
			if(strcmp(records[ptr].name, records[i].name) == 0 && records[ptr].releaseYear == records[i].releaseYear){
				count++;
				break;
			}
			ptr++;
		}
	
        }
        return count;
}
// TODO: Replace last N random
// Input: int array, number of elements to replace
// ASSUME: numToReplace <= length of arr
// Replace the last numToReplace elements with a random number
// e.g., arr = [1,2,3,4,5], numToReplace=2
// Output: arr = [1,2,3,383100999,858300821]
// ONLY USE rand() function. `man 3 rand`
void replaceLastNRandom(int* arr, int numElements, int numToReplace) {
	// Do not touch this line
	// Required for auto-grader
	srand(12345);
	// use rand() to generate a random number
	for(int i = numElements - numToReplace; i < numElements; i++){
		arr[i] = rand();
	}
	return;
}

int main(int argc, char* argv[]) {
	// argc - number of cmd line args
	// argv - array of cmd line args

	// Step 1: Ensure at least two command line args were given
	// e.g., ./hw1 {transformArray|numDuplicates|replaceLastNRandom}
	if (argc < 2) {
		// NOTE: Notice how we must include a new line char (\n)
		// NOTE: What is stderr? What is the difference between stdout & stderr?
		fprintf(stderr, "Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}\n");
		// NOTE: EXIT_FAILURE is a macro. This makes our code cleaner.
		return EXIT_FAILURE;
	}

	// Step 2: Now that we know what exercise to run, let's setup conditionals
	// to enforce this
	// NOTE: In your terminal, run `man strcmp`: This will give us the documentation
	// strcmp(char*, char*) -> 0 if eq
	// NOTE: Why is it argv[1]? What is argv[0]?
	if (strcmp(argv[1], "transformArray") == 0) {
		// At this point, the user has entered ./hw1 transformArray ...
		// The following code will setup our 2d array.
		// It is not necessary to understand this code yet, but take a stab at it.

		// ./hw1 transformArray {rows} {cols} {elements}
		// atoi converts a char* to an int
		int rows = atoi(argv[2]);
		int cols = atoi(argv[3]);
		// We are taking a 2d array as input
		// Thus, rows*cols is the number of elements in the array
		// We need to add 4 to skip the first four arguments: 
		// program name, exercise name, num rows, num cols
		if ((rows * cols) + 4 != argc) {
			fprintf(stderr, "Usage: ./hw1 transformArray {rows} {cols} {rows*cols elements}\n");
			return EXIT_FAILURE;
		}

		// We are now ready to load the 2d array into memory
		// THIS IS OUR INPUT 2D ARRAY
		// first, we need to allocate enough room for num rows arrays
		int** arr = (int**)malloc(rows * sizeof(int*));
		for (int i = 0; i < rows; i++) {
			// now, lets allocate enough room for num cols elements in each array
			arr[i] = (int*)malloc(cols * sizeof(int));
			for (int j = 0; j < cols; j++) {
				// now lets load the elements
				arr[i][j] = atoi(argv[4 + i * cols + j]);
			}
		}

		// Now arr is a 2d array loaded with elements from command line args
		// Step 3: Call your transformArray function
		// This function will reverse the halves of every row in the array in-place
		// Thus, no need for a return value.
		transformArray(arr, rows, cols);

		// Now our arr is transformed. 

		// DO NOT TOUCH THE FOLLOWING CODE
		// FORMAT IS REQUIRED FOR AUTO-GRADER
		// ANY CHANGES WILL RESULT IN INVALID SCORE
		// Print the transformed 2D array
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%d ", arr[i][j]);
			}
			printf("\n");
			free(arr[i]);
		}
		free(arr);
	} else if (strcmp(argv[1], "numDuplicates") == 0) {
		// At this point, the user has entered ./hw1 numDuplicates ...
		// each struct requires 3 elements: id, name, release year

		// ./hw1 numDuplicates {numRecords} {data}
		// ./hw1 numDuplicates 2 1 recordA 1970 2 recordA 1970
		int numRecords = atoi(argv[2]);

		if (argc != (numRecords*3) + 3) {
			fprintf(stderr, "Usage: ./hw1 numDuplicates {numRecords} {data}\n");
			return EXIT_FAILURE;
		}

		// allocate enough space for an array of numRecords record_t structs.
		record_t* records = (record_t*)malloc(numRecords * sizeof(record_t));
		// load the data
		for (int i = 0; i < numRecords; i++) {
			records[i].id = atoi(argv[3 + i * 3]);
			records[i].name = strdup(argv[4 + i * 3]);
			// STEP 4: Add the data for Release Year. Use the examples above for assistance.
			// What function should you use to convert a char* to int?
                        records[i].releaseYear = atoi(argv[5 + i * 3]);
		}

		int result = numDuplicates(records, numRecords);

		// DO NOT TOUCH THE FOLLOWING CODE
		// FORMAT IS REQUIRED FOR AUTO-GRADER
		// ANY CHANGES WILL RESULT IN INVALID SCORE
		// Print the result
		printf("%d", result);

		// release allocated memory
		// Why do we need to free name first before the entire array?
		// a char* is a dynamically alloc string => We do not know how long the string is
		// until the user enters it.
		// We have to free the inside of the array, before the entire array
		// else, that memory will forever be allocated
		for (int i = 0; i < numRecords; i++) {
			free(records[i].name);
		}
		free(records);
	} else if (strcmp(argv[1], "replaceLastNRandom") == 0) {
		// At this point user has entered ./hw1 replaceLastNRandom ...

		// STEP 5: Extract numToReplace and numElements
		int numToReplace = atoi(argv[2]);
		int numElements = atoi(argv[3]);
		// STEP 6: Add a check to ensure user has passed correct num of args
		// check "transformArray" for an example
		// ./hw1 replaceLastNRandom {numToReplace} {numElements} {elements}
		// ./hw1 replaceLastNRandom 2 5 1 2 3 4 5
		// You can assume numToReplace <= numElements
		// You can assume all elements will be integers
		if(numElements + 4 != argc){
			fprintf(stderr, "Usage: ./hw1 replaceLastNRandom {numToReplace} {numElements} {elements}\n");
			return EXIT_FAILURE;
		}

		// STEP 7: Now load the array into memory
		// allocate enough space for a variable named arr
		// iterate over all elements and load them into their respective slots
		int *arr = (int*)malloc(numElements * sizeof(int));
		for(int i = 0; i < numElements; i++){
			arr[i] = atoi(argv[i + 4]);
		}

		// STEP 8: replace the last numToReplace elements in the array
		replaceLastNRandom(arr, numElements, numToReplace);

		// STEP 9: Modify numElements and arr variable name as needed.
		// DO NOT touch print statement, this is used for auto-grader
		// output should be:
		// 1 2 3 4 5
		for (int i = 0; i < numElements; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");

		// STEP 10: Free the allocated memory
		free(arr);
	} else {
		// STEP 11: Account for cases where the user passes in arguments
		// other than what we are expecting

		// STEP 11a. Print to stderr "Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}\n"
		fprintf(stderr, "Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}\n");
		// STEP 11b. return the failure macro
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
