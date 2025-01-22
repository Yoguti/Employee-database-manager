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
- **Custom headers**:
  - `file.h`: Functions for file creation, opening, and validation.
  - `common.h`: Shared constants.
  - `parse.h`: Functions to parse and manipulate employee data.`

#### Options:
| Option         | Description                                       |
|----------------|---------------------------------------------------|
| `-n`           | Create a new database file.                      |
| `-f <filepath>`| Specify the database file (required).            |
| `-a <string>`  | Add an employee to the database.                 |
| `-r <string>`  | Remove an employee from the database.            |
| `-h <string>`  | Update hours worked for a specific employee.     |
| `-l`           | List all employees in the database.              |

### Example Usage

1. **Create a new database file**:
   ```bash
   ./employee_db_manager -n -f employees.db
   ```

2. **Add an employee**:
   ```bash
   ./employee_db_manager -f employees.db -a "John Doe,Software Engineer,40"
   ```

3. **Remove an employee**:
   ```bash
   ./employee_db_manager -f employees.db -r "John Doe"
   ```

4. **Update hours**:
   ```bash
   ./employee_db_manager -f employees.db -h "John Doe,45"
   ```

5. **List all employees**:
   ```bash
   ./employee_db_manager -f employees.db -l
   ```

### Build Instructions

To compile the project, simply run:
```bash
make
```
This will generate the executable in the `bin/` directory. To run the program, use:
```bash
make run
```
If you want to clean the build files, use:
```bash
make clean
```




