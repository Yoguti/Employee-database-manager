#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>



void print_usage(char *argv[]) {

	printf("Usage: %s -n -f <database file>\n", argv[0]);
	printf("\t -n : create a new database file\n");	
	printf("\t -f : (required) file path to the database file\n");
	return;

}

int main(int argc, char* argv[]) {

	char *filepath = NULL;
	int c;
	bool newfile = false;

	while ((c = getopt(argc, argv, "nf:")) != -1) {
		switch (c) {
			case 'n':
				newfile = true;
				break;
			case 'f':
				filepath = optarg;
				break;
			case '?':
				printf("Unknown option -%c\n", c);
				break;
			default:
				return -1;

		}

	}
	
	if (filepath == NULL) {

		printf("File path is a required argument\n");
		print_usage(argv);

	}

	printf("Newfile: %d\n", newfile);
	printf("Filepath: %s\n", filepath);


}
