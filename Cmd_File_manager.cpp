/*
1. Run the program. Display the main menu:
   a. "1. Open directory"
   b. "2. Create directory"
   c. "3. Exit"

2. Based on user input:
   a. Option 1: Open directory
      i. Prompt the user to enter the directory path.
      ii. If the directory exists:
          - Display the files in the directory.
          - Prompt user for file-related actions:
             > "1. Open file"
             > "2. Select file for copy/move"
             > "3. Return to Main Menu"
      iii. If the directory doesn’t exist:
          - Display "Invalid directory. Returning to Main Menu."

   b. Option 2: Create directory
      i. Prompt the user to enter the name of the new directory.
      ii. If the creation is successful:
          - Display "Directory created successfully."
          - Return to Main Menu.
      iii. If the directory already exists or cannot be created:
          - Display "Directory creation failed. Returning to Main Menu."

   c. Option 3: Exit
      - Display "Exiting program. Goodbye!"

3. File Operations:
   a. If "Select file for copy/move" is chosen:
      i. Prompt the user to enter the file name.
      ii. Validate if the file exists:
          - If not, display "File not found. Returning to directory menu."
      iii. If valid, prompt the user:
          - Enter "Copy" or "Move."
          - Enter destination directory path.
      iv. Perform the action:
          - If successful, display "File copied/moved successfully."
          - If failed, display "Action failed. Returning to directory menu."

4. Error Handling:
   - Invalid inputs for menu options or file operations return:
     > "Invalid action. Returning to Main Menu."

5. Repeat steps 1-4 until the user selects "Exit."



Suggestions for Improvement

    Input Validation:
        Validate inputs for menu options and paths to prevent crashes.

while (!(std::cin >> choice)) {
    std::cerr << "Invalid input. Please enter a number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Recursive Directory Navigation:

    Add an option to navigate subdirectories and display their contents.

for (const auto& entry : fs::recursive_directory_iterator(path)) {
    std::cout << entry.path().filename() << '\n';
}

Confirmation for Overwriting Files:

    Before copying or moving files, check if the destination file exists and prompt for confirmation.

if (fs::exists(destPath + "/" + filename)) {
    std::cout << "File already exists in the destination. Overwrite? (y/n): ";
    char overwrite;
    std::cin >> overwrite;
    if (overwrite != 'y') return;
}

Retry Mechanism:

    Allow users to retry tasks instead of returning to the main menu immediately after an error.

Add Additional Features:

    Support for deleting files, renaming files, or viewing file details.
    Enhance file opening to display file contents (e.g., for text files).
*/

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <limits>
#include <fstream>

namespace fs = std::filesystem;

// Function declarations
void displayMainMenu();
void openDirectory();
void createDirectory();
void displayDirectoryContents(const std::string& path, bool recursive = false);
void copyOrMoveFile(const std::string& path);
void viewFile(const std::string& path);

void displayMainMenu()
{
    std::cout << "1. Open directory\n";
    std::cout << "2. Create directory\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void openDirectory()
{
    std::string path;
    std::cout << "Enter the directory path: ";
    std::cin.ignore(); // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, path);

    if (fs::exists(path) && fs::is_directory(path))
    {
        int choice;
        std::cout << "1. Display files\n";
        std::cout << "2. Display files recursively\n";
        std::cout << "3. Copy/Move file\n";
        std::cout << "4. View file\n";
        std::cout << "5. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        while (!(std::cin >> choice))
        {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            displayDirectoryContents(path);
            break;
        case 2:
            displayDirectoryContents(path, true);
            break;
        case 3:
            copyOrMoveFile(path);
            break;
        case 4:
            viewFile(path);
            break;
        case 5:
            return;
        default:
            std::cerr << "Invalid action. Returning to Main Menu.\n";
            break;
        }
    }
    else
    {
        std::cerr << "Invalid directory. Returning to Main Menu.\n";
    }
}

void displayDirectoryContents(const std::string& path, bool recursive)
{
    if (recursive)
    {
        for (const auto& entry : fs::recursive_directory_iterator(path))
        {
            std::cout << entry.path() << '\n';
        }
    }
    else
    {
        for (const auto& entry : fs::directory_iterator(path))
        {
            std::cout << entry.path() << '\n';
        }
    }
}

void copyOrMoveFile(const std::string& path)
{
    std::string filename;
    std::string action;
    std::string destPath;

    while (true)
    {
        std::cout << "Enter the file name: ";
        std::cin.ignore(); // Ignore any leftover newline character in the input buffer
        std::getline(std::cin, filename);

        if (fs::exists(path + "/" + filename))
        {
            std::cout << "Enter 'Copy' or 'Move': ";
            std::cin >> action;

            std::cout << "Enter destination directory path: ";
            std::cin.ignore(); // Ignore any leftover newline character in the input buffer
            std::getline(std::cin, destPath);

            if (fs::exists(destPath) && fs::is_directory(destPath))
            {
                std::string destFilePath = destPath + "/" + filename;
                if (fs::exists(destFilePath))
                {
                    std::cout << "File already exists in the destination. Overwrite? (y/n): ";
                    char overwrite;
                    std::cin >> overwrite;
                    if (overwrite != 'y') continue;
                }

                try
                {
                    if (action == "Copy")
                    {
                        fs::copy(path + "/" + filename, destFilePath, fs::copy_options::overwrite_existing);
                        std::cout << "File copied successfully.\n";
                    }
                    else if (action == "Move")
                    {
                        fs::rename(path + "/" + filename, destFilePath);
                        std::cout << "File moved successfully.\n";
                    }
                    else
                    {
                        std::cerr << "Invalid action. Please enter 'Copy' or 'Move'.\n";
                        continue;
                    }
                }
                catch (const fs::filesystem_error& e)
                {
                    std::cerr << "Error: " << e.what() << '\n';
                    continue;
                }
                break;
            }
            else
            {
                std::cerr << "Invalid destination directory. Please try again.\n";
            }
        }
        else
        {
            std::cerr << "File does not exist. Please try again.\n";
        }
    }
}

void viewFile(const std::string& path)
{
    std::string filename;
    std::cout << "Enter the file name to view: ";
    std::cin.ignore(); // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, filename);

    std::string filePath = path + "/" + filename;

    if (fs::exists(filePath) && fs::is_regular_file(filePath))
    {
        std::ifstream file(filePath);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::cout << line << '\n';
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file.\n";
        }
    }
    else
    {
        std::cerr << "File does not exist or is not a regular file.\n";
    }
}

void createDirectory()
{
    std::string parentDir;
    std::cout << "Enter the parent directory path: ";
    std::cin.ignore(); // Ignore any leftover newline character in the input buffer
    std::getline(std::cin, parentDir);

    if (!fs::exists(parentDir) || !fs::is_directory(parentDir))
    {
        std::cerr << "Invalid parent directory. Returning to Main Menu.\n";
        return;
    }

    std::string dirName;
    std::cout << "Enter the name of the new directory: ";
    std::getline(std::cin, dirName);

    std::string fullPath = parentDir + "/" + dirName;

    try
    {
        fs::create_directory(fullPath);
        std::cout << "Directory created successfully.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Directory creation failed: " << e.what() << '\n';
    }
}

int main()
{
    int choice;

    do
    {
        displayMainMenu();
        while (!(std::cin >> choice))
        {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            openDirectory();
            break;
        case 2:
            createDirectory();
            break;
        case 3:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cerr << "Invalid action. Returning to Main Menu.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}