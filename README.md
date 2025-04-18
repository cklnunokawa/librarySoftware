# librarySoftware
A modular C++ library management system designed for small libraries, homeschoolers, and personal book collections. Supports user roles (Admin and Patron), book and copy tracking, and system-wide statistics.

## Features
- Add and manage users with role support
- Track books and their individual copies
- Check books in and out
- Print system statistics
- Modular, object-oriented C++ structure

## Project Structure
 - backend
    - include (Header files)
        - db (Header files related to database functionality)
    - src (Source files)
        - db (Source files related to database functionality)
- bin (Compiled output)

## Dependencies
- C++20 compiler
- SQLite3 installed for persistence features

## 🛠️ Build Instructions
This project includes a `Makefile` for easy compilation.
Running the following will compile all .cpp files from the backend/src/ directory (including nested folders) and output the executable to: bin/libraryApp
The Makefile automatically detects new source files, so you don’t need to update it every time you add a .cpp.

### To build the project:
```sh
make


### To clean the build (remove compiled binary):
make clean

## Works in Progress
- Add SQLite-based persistent storage
- API or GUI interface
- Barcode scanning support

