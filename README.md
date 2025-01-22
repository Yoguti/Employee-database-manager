# Employee Database Manager

This project is a command-line utility to manage an employee database stored in a custom binary file format. It supports creating new databases, adding employees, removing employees, updating hours, and listing all employees.

## Features

- **Create a new database file**: Initializes a new database with the necessary header and structure.
- **Add employees**: Append new employee records to the database.
- **Remove employees**: Delete specific employees from the database by their identifier.
- **Update hours**: Modify the hours worked for a specific employee.
- **List employees**: Display all employees in the database.

## Requirements

- **C Compiler**: GCC or any C99-compliant compiler.
- **Libraries**: The following headers are used:
  - `<stdio.h>`: For input/output operations.
  - `<stdlib.h>`: For memory management.
  - `<stdbool.h>`: For boolean data type support.
  - `<getopt.h>`: For command-line argument parsing.
  - `<arpa/inet.h>`: For network byte order conversions.
  - Custom headers:
    - `file.h`
    - `common.h`
    - `parse.h`

## Usage

### Command-Line Arguments

```bash
./employee_db_manager -n -f <database file> [-a <string>] [-r <string>] [-h <string>] [-l]
