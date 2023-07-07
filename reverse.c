//Harjoitusprojekti 1: Warming up program: Reverse.c
//Sources: We have taken hint from the C-programming guide: https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list{ 

    char * item; 

    struct linked_list *pNext;  

} LINKED_LIST;  

LINKED_LIST* addToList(LINKED_LIST *pNew, LINKED_LIST *pStart, LINKED_LIST *pEnd, char *line) {
	pNew->item = line;  
    pNew->pNext = NULL;  
    if (pStart == NULL) { 
        pStart = pNew;  
        pEnd = pNew;  
    } else { 
        pEnd->pNext = pNew;  
        pEnd = pNew;  
    } 
	return pStart; 
}

int main(int argc, char * argv[]) {
	LINKED_LIST *pStart = NULL, *pEnd = NULL; 
    LINKED_LIST *pNew, *ptr;  
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
			}
			//How to use getline() function: https://c-for-dummies.com/blog/?p=5445 
			char *line=NULL;
			size_t len;
			int read; 
			int lineCounter=0; 
			if((pNew = (LINKED_LIST*)malloc(sizeof(LINKED_LIST))) == NULL) { 
                perror("Error in memory allocation");  
                 exit(1);  
        } 
			do {
				read = getline(&line, &len, inputFile);
				//if (read != -1 ) {
				pStart = addToList(pNew, pStart, pEnd, line);
					//fprintf(outputFile, line);
					lineCounter++; 
				//}
			} while (read > 1);

			printf("Lines in the file: %d\n", lineCounter);
			//Printing the elements of linked list
			ptr = pStart;  
                while(ptr != NULL) { 
                    printf("Elements: %s, ", ptr->item); 
                    ptr=ptr->pNext;  
                }
			//Ending program, freeing all memory:					 
			 ptr = pStart;
            while(ptr != NULL) { 
                pStart = ptr->pNext;  
                free(ptr);  
                ptr = pStart; 

            }  
			free(line); 
			fclose(inputFile);

		}
		

	}
	//Writing to input.txt file: 
	

	//Reading input.txt reverse and writing to output.txt

	return(0);
}
