#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>



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
	
	printf("Newfile: %d\n", newfile);
	printf("Filepath: %s\n", filepath);


}
