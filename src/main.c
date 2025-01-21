#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "file.h"
#include "common.h"
#include <arpa/inet.h>
#include "parse.h"

void print_usage(char *argv[])
{
    printf("Usage: %s -n -f <database file> [-a <string>]\n", argv[0]);
    printf("\t -n : create a new database file\n");
    printf("\t -f : (required) file path to the database file\n");
    printf("\t -a : add string to database\n");
    return;
}

int main(int argc, char *argv[])
{

	int dbfd = -1;
	char *filepath = NULL;
	char *addstring = NULL;
	char *removestring = NULL;
	int c;
	bool newfile = false; 
	bool list = false;
	struct dbheader_t *dbhdr = NULL;
	struct employee_t *employees = NULL;

	while ((c = getopt(argc, argv, "nf:a:l")) != -1)
	{
		switch (c)
		{
		case 'n':
			newfile = true;
			break;
		case 'r':
			removestring = optarg;
			break;
		case 'l':
			list = true;
			break;
		case 'f':
			filepath = optarg;
			break;
		case 'a':
    		addstring = optarg;
    		break;
		case '?':
		    print_usage(argv);
    		return -1;
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
		if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR)
		{
			printf("Failed to create database header\n");
			return -1;
		}
	}

	else
	{
		dbfd = open_db_file(filepath);
		if (dbfd < 0)
		{
			printf("Unable to open database file\n");
			return -1;
		}
		if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR)
		{
			printf("Unable to validate database header file\n");
			return -1;
		}
	}

	printf("Newfile: %d\n", newfile);
	printf("Filepath: %s\n", filepath);

	if (read_employees(dbfd, dbhdr, &employees) != STATUS_SUCESS) {
			printf("Unable to read employees\n");
			return -1;		
	}

	if (addstring) {
		dbhdr->count++;
		employees = realloc(employees, dbhdr->count * (sizeof(struct employee_t)));
		add_employee(dbhdr, employees, addstring);
	}

	if(list) {
		list_employees(dbhdr, employees);
	}

	if (removestring) {
		if (remove_employee(dbhdr, &employees, removestring) != STATUS_ERROR) {
			dbhdr->count--;
		}
	}

	output_file(dbfd, dbhdr, employees);

	return 0;
}
