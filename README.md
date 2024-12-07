## DataVault-C

A lightweight C-based database management system featuring CRUD operations, bubble sort implementation, and robust file handling. Built with memory-safe operations and comprehensive error handling.

## Features

- Create, Read, Update, Delete (CRUD) operations
- Search functionality across all fields
- Sorting by any field (ID, Name, Age, Email)
- Memory-safe implementation
- File-based data persistence
- Progress indicators for long operations
- Comprehensive error handling

## Prerequisites

- GCC compiler
- Make build system
- Git (for version control)

## Installation

1. Clone the repository
```bash
git clone https://github.com/AshleydVon/DataVault-C.git
cd DataVault-C
```

## Menu Options

1. Add Record - Create new database entry
2. View Record - Retrieve specific record by ID
3. Update Record - Modify existing record
4. Delete Record - Remove record by ID
5. Search Records - Find records matching search term
6. Sort Records - Order records by chosen field
7. Display All Records - Show complete database
0. Exit - Close program

## Project Structure

```
DataVault-C/
├── src/
│   ├── main.c
│   ├── database.c
│   ├── database.h
│   └── operations.c
├── data/
│   └── records.dat
└── Makefile
```

## Technical Details

- Written in C
- Uses file-based storage system
- Implements bubble sort algorithm
- Binary file handling for data persistence
- Dynamic memory management
- Input validation and error handling

## Error Handling

The program includes comprehensive error checking for:
- File operations
- Memory allocation
- Input validation
- Database operations
- Sort operations

## Contributing

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open Pull Request

## License

Distributed under the MIT License. See LICENSE for more information.

## Contact

Your Name - @AshleydVon

Project Link: https://github.com/AshleydVon/DataVault-C

## Acknowledgments

- Bubble Sort Implementation
- File Handling in C
- Memory Management Best Practices