//Harjoitusprojekti 1: Warming up program: Reverse.c
//Sources: We have taken hint from the C-programming guide: https://lutpub.lut.fi/bitstream/handle/10024/162908/Nikula2021-COhjelmointiopasV21.pdf?sequence=1&isAllowed=y
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
			//char lines[];
			do {
				read = getline(&line, &len, inputFile);
				if (read != -1 ) {
					printf("%s", line);
					//fprintf(outputFile, line);
					lineCounter++; 
				}
			} while (read > 1);
			printf("Lines in the file: %d\n", lineCounter);

			free(line); 
			fclose(inputFile);

		}
		

	}
	//Writing to input.txt file: 
	

	//Reading input.txt reverse and writing to output.txt

	return(0);
}
