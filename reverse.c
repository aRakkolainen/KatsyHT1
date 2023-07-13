//Harjoitusprojekti 1: Warming up program: Reverse.c
//Sources: We have taken help from the C-programming guide: https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list{ 
    char * line;
	int iLinenumber; 
    struct linked_list *pNext;  
} LINKED_LIST;  

//Introducing functions: 

LINKED_LIST *addToList(LINKED_LIST *, int, char *,  int);
void printInReverseOrder(LINKED_LIST *);
LINKED_LIST * writeReverseOrderToOutputFile(LINKED_LIST *, FILE *);
LINKED_LIST *freeTheMemory(LINKED_LIST *);


//Adding to the linked list is based on the C-programming guide
LINKED_LIST * addToList(LINKED_LIST *pStart, int lineLength, char *line, int lineNum) {
	LINKED_LIST *pNew, *ptr;
	int memory; 
	//printf("%s", line); 
	if ((pNew = (LINKED_LIST*)malloc(sizeof(LINKED_LIST))) == NULL) {
		fprintf(stderr, "error: malloc failed");
		exit(1);
	}
	// Based on the C-programming guide example 5.4 Dynamic memory allocation
	pNew->line = NULL;
	memory = lineLength * sizeof(char);
	if ((pNew->line = (char *)malloc(memory)) == NULL) {
		fprintf(stderr, "error: malloc failed");
		exit(1);
	}
	// Setting values for new list item
	strcpy(pNew->line, line);
	pNew->iLinenumber=lineNum; 
    pNew->pNext = NULL;  
	// Checking whether the list is empty or not and proceeding accordingly
    if (pStart == NULL) { 
        pStart=pNew;    
    } else { 
		ptr = pStart; 
		while (ptr->pNext != NULL) 
			ptr=ptr->pNext;
		ptr->pNext = pNew;		
    }
	return pStart;   
}

// This function is based on this source: https://www.geeksforgeeks.org/print-reverse-of-a-linked-list-without-actually-reversing/ 
void printInReverseOrder(LINKED_LIST *pStart) {
	//LINKED_LIST *ptr = pStart; 
	//printf("Line number: %d, content: %s", ptr->iLinenumber, ptr->line);
	//ptr = ptr->pNext; 
	//printf("Line number: %d, content: %s", ptr->iLinenumber, ptr->line);
	/*while (ptr != NULL) {
		printf("Line number: %d, content: %s", ptr->iLinenumber, ptr->line);
		ptr = ptr->pNext;
	}*/

	if (pStart == NULL) {
		return; 
	}
	printInReverseOrder(pStart->pNext);
	printf("%s", pStart->line);

}

LINKED_LIST * writeReverseOrderToOutputFile(LINKED_LIST *pStart, FILE *output) { 
	if (pStart == NULL) {
		return pStart; 
	}
	writeReverseOrderToOutputFile(pStart->pNext, output);
	fprintf(output, "%s", pStart->line);
	return pStart; 
}

LINKED_LIST *freeTheMemory(LINKED_LIST *pStart) {
	LINKED_LIST *ptr = pStart;
	while (ptr != NULL) {
		pStart = ptr->pNext; 
		free(ptr);
		//free(ptr->line);
		ptr = pStart; 
	}
	return(pStart);
}
int main(int argc, char * argv[]) {  
	LINKED_LIST *pStart = NULL;
	char *line=NULL; 
	size_t len;
	int readLineLength; 
	int lineCounter=1;
	char inputFileName[30];
	char outputFileName[30];
	FILE *inputFile;
	FILE *outputFile;
	if (argc == 0) {
		printf("No command-line arguments given\n");
	}
	else if (argc == 1) {
		printf("Standard input and output\n");

	} else if (argc == 2) {
		printf("Reading input file and reversing to stdin\n");
		strcpy(inputFileName, argv[1]);
		if ((inputFile = fopen(inputFileName, "r")) == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n", inputFileName);
			exit(1);
		} else {
				//How to use getline() function: https://c-for-dummies.com/blog/?p=5445 
				// Using getline() function: https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline-- 
			do {
				readLineLength = getline(&line, &len, inputFile); 
				if (readLineLength != -1) {
					pStart=addToList(pStart, readLineLength, line, lineCounter);
					lineCounter++;  
				}
			} while ( readLineLength > 1);
			}
			fclose(inputFile);
			printInReverseOrder(pStart);
			freeTheMemory(pStart);
		} else if (argc == 3) {
			if (argv[1] == argv[2]) {
				perror("Input and ouput file must differ\n"); 
				exit(1);
			}
			printf("Reading input.txt and reversing the content in the file output.txt\n");
			strcpy(inputFileName, argv[1]);
			strcpy(outputFileName, argv[2]);
		// Opening the input file 
			if ((inputFile = fopen(inputFileName, "r")) == NULL) {
				fprintf(stderr, "error: cannot open file '%s'\n", inputFileName);
				exit(1);
			} else {
				if((outputFile = fopen(outputFileName, "w")) == NULL) {
					fprintf(stderr, "error: cannot open file '%s'\n", outputFileName);
				} else {
				//How to use getline() function: https://c-for-dummies.com/blog/?p=5445 
				// Using getline() function: https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline-- 
				do {
					readLineLength = getline(&line, &len, inputFile); 
					if (readLineLength != -1) {
						pStart=addToList(pStart, readLineLength, line, lineCounter);
						lineCounter++;  
					}
				} while ( readLineLength > 1);

				writeReverseOrderToOutputFile(pStart, outputFile);
				//Ending program, closing files and freeing all memory:	
				fclose(outputFile);
				fclose(inputFile);				 
				free(line);
				freeTheMemory(pStart); 

		}
	}
	//Writing to input.txt file: 
	

	//Reading input.txt reverse and writing to output.txt
	}
	return(0);
}
