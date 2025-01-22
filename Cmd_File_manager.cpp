#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

void displayMainMenu();
void openDirectory();
void createDirectory();
void displayDirectoryContents(const std::string& path, bool recursive = false);
void copyFile(const std::string& path);
void moveFile(const std::string& path);
void viewFile(const std::string& path);
bool isValidPath(const std::string& path);
std::string normalizePath(const std::string& path);

void displayMainMenu() {
    std::cout << "\n1. Open directory\n"
              << "2. Create directory\n"
              << "3. Exit\n"
              << "Enter your choice: ";
}

std::string normalizePath(const std::string& path) {
    std::string normalized = path;
    std::replace(normalized.begin(), normalized.end(), '\\', '/');
    normalized.erase(normalized.find_last_not_of(" \t\n\r\f\v") + 1);
    return normalized;
}

bool isValidPath(const std::string& path) {
    std::regex pattern(R"(^([a-zA-Z]:[\\/])?([^<>:\"|?*]+[\\/])*[^<>:\"|?*]*$)");
    return std::regex_match(path, pattern);
}

void openDirectory() {
    std::string path;
    std::cout << "Enter the directory path: ";
    std::cin.ignore();
    std::getline(std::cin, path);
    path = normalizePath(path);

    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cerr << "Invalid directory path.\n";
        return;
    }

    int choice;
    std::cout << "\n1. Display files\n"
              << "2. Display files recursively\n"
              << "3. Copy file\n"
              << "4. Move file\n"
              << "5. View file\n"
              << "6. Return to Main Menu\n"
              << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: displayDirectoryContents(path); break;
        case 2: displayDirectoryContents(path, true); break;
        case 3: copyFile(path); break;
        case 4: moveFile(path); break;
        case 5: viewFile(path); break;
        case 6: return;
        default: std::cerr << "Invalid choice.\n"; break;
    }
}

void createDirectory() {
    std::string path;
    std::cout << "Enter the directory path to create: ";
    std::cin.ignore();
    std::getline(std::cin, path);
    path = normalizePath(path);

    if (fs::exists(path)) {
        std::cerr << "Directory already exists.\n";
        return;
    }

    try {
        if (fs::create_directories(path)) {
            std::cout << "Directory created successfully.\n";
        } else {
            std::cerr << "Failed to create directory.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void displayDirectoryContents(const std::string& path, bool recursive) {
    try {
        if (recursive) {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                std::cout << entry.path() << '\n';
            }
        } else {
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << entry.path() << '\n';
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void copyFile(const std::string& sourceDir) {
    std::string filename, destPath;
    std::cout << "Enter the file name to copy: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the destination directory path: ";
    std::getline(std::cin, destPath);

    std::string sourceFilePath = normalizePath(sourceDir + "/" + filename);
    destPath = normalizePath(destPath + "/" + filename);

    if (!fs::exists(sourceFilePath) || !fs::is_regular_file(sourceFilePath)) {
        std::cerr << "Source file does not exist.\n";
        return;
    }
    if (!fs::exists(destPath)) {
        std::cerr << "Destination path is invalid.\n";
        return;
    }

    try {
        fs::copy(sourceFilePath, destPath, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully to " << destPath << '\n';
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Copy failed: " << e.what() << '\n';
    }
}

void moveFile(const std::string& sourceDir) {
    std::string filename, destPath;
    std::cout << "Enter the file name to move: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the destination directory path: ";
    std::getline(std::cin, destPath);

    std::string sourceFilePath = normalizePath(sourceDir + "/" + filename);
    std::string destFilePath = normalizePath(destPath + "/" + filename);

    if (!fs::exists(sourceFilePath) || !fs::is_regular_file(sourceFilePath)) {
        std::cerr << "Source file does not exist.\n";
        return;
    }
    if (!fs::exists(destPath)) {
        std::cerr << "Destination path is invalid.\n";
        return;
    }

    try {
        fs::rename(sourceFilePath, destFilePath);
        std::cout << "File moved successfully to " << destFilePath << '\n';
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Move failed: " << e.what() << '\n';
    }
}

void viewFile(const std::string& path) {
    std::string filename;
    std::cout << "Enter the file name to view: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    std::string filePath = normalizePath(path + "/" + filename);
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        std::cerr << "File does not exist or is not a regular file.\n";
        return;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
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