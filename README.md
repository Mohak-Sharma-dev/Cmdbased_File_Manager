# Command-Line Interface (CLI) File Manager

A C++-based Command-Line Interface (CLI) file manager designed to perform various file and directory operations with ease. This tool aims to replicate the functionality of GUI file managers in a terminal environment, supporting multiple platforms such as Windows, macOS, and Linux.

---

## Features

### 📂 Directory Navigation
- **Normal Display**: View all files and subdirectories in the current directory.  
- **Recursive Display**: Explore all nested files and subdirectories recursively.  

### 📄 File Operations
- **View File**: Open and view the contents of text files directly in the terminal.  
- **Copy Files**: Copy files from one directory to another with overwrite handling.  
- **Move Files**: Move files between directories, creating destination directories if needed.  

### ✅ Input Validation
- Uses regex to validate file paths, ensuring proper formatting and preventing invalid operations.

### 🌍 Cross-Platform Compatibility
- Built using the `<filesystem>` library for consistent functionality across Windows, macOS, and Linux.  

### ⚙️ Error Handling
- Displays clear, actionable error messages for invalid paths, missing files, or insufficient permissions.

---

