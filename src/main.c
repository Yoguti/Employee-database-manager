#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include "file.h"
#include "common.h"

void print_usage(char *argv[])
{

	printf("Usage: %s -n -f <database file>\n", argv[0]);
	printf("\t -n : create a new database file\n");
	printf("\t -f : (required) file path to the database file\n");
	return;
}

int main(int argc, char *argv[])
{

	int dbfd = -1;
	char *filepath = NULL;
	int c;
	bool newfile = false;
	struct dbhdr_t *dbhdr = NULL;

	while ((c = getopt(argc, argv, "nf:")) != -1)
	{
		switch (c)
		{
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

	if (filepath == NULL)
	{

		printf("File path is a required argument\n");
		print_usage(argv);

		return 0;
	}

	if (newfile)
	{
		dbfd = create_db_file(filepath);
		if (dbfd == STATUS_ERROR)
		{
			printf("Unable to create database file\n");
			return -1;
		}
		if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
			printf("Failed to create database header\n");
			return -1;
		}
	}
	dbfd = open_db_file(filepath);
	if (dbfd < 0)
	{
		printf("Unable to open database file\n");
		return -1;
	}

	if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
		printf("Unable to validate database header file\n");
		return -1;
	}

	printf("Newfile: %d\n", newfile);
	printf("Filepath: %s\n", filepath);
}
