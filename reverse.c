//Harjoitusprojekti 1: Warming up program: Reverse.c
//Sources: We have taken hint from the C-programming guide: https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list{ 
    char * line;
	int iLinenumber; 
    struct linked_list *pNext;  
} LINKED_LIST;  

//Introducing functions: 

LINKED_LIST *addToList(LINKED_LIST *, char *,  int);
LINKED_LIST *printInReverseOrder(LINKED_LIST *);
LINKED_LIST * addToList(LINKED_LIST *pStart, char *line, int lineNum) {
	LINKED_LIST *pNew, *ptr;
	char * newLine = (char *) malloc(sizeof(line));
	//printf("%s", line); 
	if ((pNew = (LINKED_LIST*)malloc(sizeof(LINKED_LIST))) == NULL) {
		fprintf(stderr, "error: malloc failed");
		exit(1);
	}
	//Setting the values of the new item (line read from file) 
	printf("%s", line);
	strcpy(newLine, line);
	strcpy(pNew->line, newLine);
	printf("%s", pNew->line);
	pNew->iLinenumber=lineNum; 
    pNew->pNext = NULL;  
    if (pStart == NULL) { 
        pStart=pNew;    
    } else { 
		ptr = pStart; 
		while (ptr->pNext != NULL) {
			ptr=ptr->pNext;
			ptr->pNext = pNew;
		}
    }
	//strcpy(pNew->line, line);
	return pStart;   
}

LINKED_LIST *printInReverseOrder(LINKED_LIST *pStart) {
	LINKED_LIST *ptr = pStart; 
	while (ptr != NULL) {
		printf("%d\n", ptr->iLinenumber);
		ptr = ptr->pNext;
	}
	return(pStart);

}

LINKED_LIST *freeTheMemory(LINKED_LIST *pStart) {
	LINKED_LIST *ptr = pStart;
	while (ptr != NULL) {
		pStart = ptr->pNext; 
		free(ptr);
		ptr = pStart; 
	}
	return(pStart);
}
int main(int argc, char * argv[]) { 
	if (argc == 0) {
		printf("No command-line arguments given\n");
	}
	else if (argc == 1) {
		printf("Standard input and output\n");

	} else if (argc == 2) {
		printf("Reading input file and reversing to stdin\n");
	} else if (argc == 3) {
		if (argv[1] == argv[2]) {
			perror("Input and ouput file must differ\n"); 
			exit(1);
		}
		LINKED_LIST *pStart = NULL;
		char *line=NULL;
		size_t len;
		int read; 
		int lineCounter=0;
		printf("Reading input.txt and reversing the content in the file output.txt\n");
		char inputFileName[30];
		strcpy(inputFileName, argv[1]);
		char outputFileName[30];
		strcpy(outputFileName, argv[2]);
		FILE *inputFile;
		FILE *outputFile;

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
			while ((read = getline(&line, &len, inputFile)) != -1 ) {
					//printf("%s at line %d ", line, lineCounter);
					lineCounter++;
					//printf("%s", line);
					pStart=addToList(pStart, line, lineCounter);
			}
			
			//printf("Lines in the file: %d\n", lineCounter);
			//Printing the elements of linked list
			printInReverseOrder(pStart);
			fclose(inputFile);
			//Ending program, freeing all memory:					 
			free(line);
			freeTheMemory(pStart); 
			}
	
		}
		

	}
	//Writing to input.txt file: 
	

	//Reading input.txt reverse and writing to output.txt

	return(0);
}
