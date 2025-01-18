# Command-Line File Manager

A simple command-line interface (CLI) file manager built in C++ that allows users to navigate directories, view files, create directories, and copy/move files. This project showcases the use of modern C++ features such as the `<filesystem>` library, error handling, and input validation to ensure cross-platform functionality.

---

## **Key Features**  

- **Directory Navigation**  
  - Open directories and list their contents (regular or recursive listing).
  - Validate and handle invalid directory paths.

- **File Operations**  
  - View the contents of text files.  
  - Copy or move files to a specified destination with overwrite confirmation.

- **Directory Creation**  
  - Create new directories in specified parent directories with path validation.

- **Input Validation**  
  - Handles invalid user inputs gracefully using `std::limits` and regex-based path validation.

- **Cross-Platform Compatibility**  
  - Works on Windows, Mac, and Linux systems using the modern `<filesystem>` library.

---

## **Challenges Faced and Solutions**  

1. **Cross-Platform Compatibility**  
   - **Challenge**: Ensuring the program works seamlessly on different operating systems.
   - **Solution**: Utilized the `<filesystem>` library for platform-independent file operations and tested on multiple platforms.

2. **Error Handling**  
   - **Challenge**: Preventing crashes due to invalid user inputs or file operations.  
   - **Solution**: Implemented robust error handling with `std::cerr` for clear error messages and `try-catch` blocks for exception management.

3. **Path Validation**  
   - **Challenge**: Allowing only valid paths to avoid unintended behavior or security issues.  
   - **Solution**: Created an `isValidPath()` function using regex to validate directory and file paths.

---

## **Code Explanation**

### **Why Use `<filesystem>`?**  
The `<filesystem>` library provides a modern and portable way to perform file and directory operations, such as checking existence, creating directories, listing contents, copying files, and more. It ensures compatibility across Windows, Mac, and Linux.

### **Why Use `std::cerr` Instead of `std::cout`?**  
`std::cerr` is used to display error messages. It writes to the standard error stream (stderr), allowing errors to be separated from normal program output. This separation improves debugging and logging.

### **Why Use `std::limits`?**  
`std::limits` ensures robust input validation by clearing invalid input and preventing infinite loops when users enter incorrect data types.

### **Why Use `isValidPath()`?**  
The `isValidPath()` function validates directory and file paths using a regex pattern, ensuring they contain only safe characters. This prevents security vulnerabilities and ensures compatibility with file systems.

---

### **Steps to Run**
1. Clone the repository:
   ```bash
   git clone https://github.com/Mohak-Sharma-dev/CodeAlpha_Cmdbased_File_Manager.git
