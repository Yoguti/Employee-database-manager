#include "common.h"
#include "parse.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int remove_employee(struct dbheader_t *dbhrd, struct employee_t **employees, char *name_id)
{
	int i = 0;
	int j = -1;
	for (; i < dbhrd->count; i++)
	{
		if (strcmp((*employees)[i].name, name_id) == 0)
		{
			j = i;
		}
	}

	if (j != -1)
	{
		for (int i = j; i < dbhrd->count; i++)
		{
			(*employees)[i] = (*employees)[i + 1];
		}
	}
	else
	{
		printf("Employee not found in database");
		return STATUS_ERROR;
	}

	struct employee_t *temp = realloc(*employees, (dbhrd->count) * sizeof(struct employee_t));

	if (temp == NULL && dbhrd->count > 0)
	{
		printf("Failed to reallocate memory.\n");
		return STATUS_ERROR;
	}

	*employees = temp;

	return STATUS_SUCESS;
}

void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees)
{
	int i = 0;
	for (; i < dbhdr->count; i++)
	{
		printf("Employee d%\n", i);
		printf("\tName: %s\n", employees[i].name);
		printf("\tAddress: %s\n", employees[i].address);
		printf("\tHours: %d\n", employees[i].hours);
	}
}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring)
{
	char *name = strtok(addstring, ",");
	char *addr = strtok(NULL, ",");
	char *hours = strtok(NULL, ",");

	strncpy(employees[dbhdr->count - 1].name, name, sizeof(employees[dbhdr->count - 1].name));
	strncpy(employees[dbhdr->count - 1].address, addr, sizeof(employees[dbhdr->count - 1].address));
	employees[dbhdr->count - 1].hours = atoi(hours);

	return STATUS_SUCESS;
}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees)
{
	if (fd < 0)
	{
		printf("Bad FD from the user");
		return STATUS_ERROR;
	}

	int realcount = dbhdr->count;

	dbhdr->magic = htonl(dbhdr->magic);
	dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount));
	dbhdr->count = htons(dbhdr->count);
	dbhdr->version = htons(dbhdr->version);

	lseek(fd, 0, SEEK_SET);
	write(fd, dbhdr, sizeof(struct dbheader_t));

	int i = 0;
	for (; i < realcount; i++)
	{
		employees[i].hours = htonl(employees[i].hours);
		write(fd, &employees[i], sizeof(struct employee_t));
	}
}

int create_db_header(int fd, struct dbheader_t **headerOut)
{
	struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
	if (header == NULL)
	{
		printf("Calloc failed to create db header\n");
		return STATUS_ERROR;
	}
	header->version = 0x1;
	header->count = 0;
	header->magic = HEADER_MAGIC;
	header->filesize = sizeof(struct dbheader_t);
	*headerOut = header;

	return STATUS_SUCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut)
{
	if (fd < 0)
	{
		printf("Bad FD from the user");
		return STATUS_ERROR;
	}

	struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
	if (header == NULL)
	{
		printf("Calloc error");
		return STATUS_ERROR;
	}

	if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t))
	{
		perror("read");
		free(header);
		return STATUS_ERROR;
	}
	header->version = ntohs(header->version);
	header->count = ntohs(header->count);
	header->magic = ntohl(header->magic);
	header->filesize = ntohl(header->filesize);

	if (header->version != 0x1)
	{
		printf("Improper header version\n");
		free(header);
		return -1;
	}
	if (header->magic != HEADER_MAGIC)
	{
		printf("Improper header magic\n");
		free(header);
		return -1;
	}
	struct stat dbstat = {0};
	fstat(fd, &dbstat);

	if (header->filesize != dbstat.st_size)
	{
		printf("Corrupted database");
		free(header);
		return -1;
	}
	*headerOut = header;
	return STATUS_SUCESS;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut)
{
	if (fd < 0)
	{
		printf("Bad FD from the user");
		return STATUS_ERROR;
	}
	int count = dbhdr->count;

	struct employee_t *employees = calloc(count, sizeof(struct employee_t));
	if (employees == NULL)
	{
		printf("Calloc error");
		return STATUS_ERROR;
	}

	read(fd, employees, count * sizeof(struct employee_t));

	int i = 0;

	for (; i < count; i++)
	{
		employees[i].hours = ntohl(employees[i].hours);
	}

	*employeesOut = employees;
	return STATUS_SUCESS;
}
