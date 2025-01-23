#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

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
    std::cout << "\nMain Menu:\n"
              << "1. Open directory (perform operations like view, move, or copy files)\n"
              << "2. Create a new directory\n"
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
    std::cout << "Enter the full path of the directory to open: ";
    std::cin.ignore();
    std::getline(std::cin, path);
    path = normalizePath(path);

    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cerr << "Error: Invalid directory path.\n";
        return;
    }

    int choice;
    std::cout << "\nDirectory Operations:\n"
              << "1. Display files in the directory\n"
              << "2. Display files recursively (including subdirectories)\n"
              << "3. Copy a file from this directory\n"
              << "4. Move a file from this directory\n"
              << "5. View the contents of a text file\n"
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
        default: std::cerr << "Invalid choice. Returning to Main Menu.\n"; break;
    }
}

void createDirectory() {
    std::string path;
    std::cout << "Enter the full path of the new directory to create: ";
    std::cin.ignore();
    std::getline(std::cin, path);
    path = normalizePath(path);

    if (fs::exists(path)) {
        std::cerr << "Error: Directory already exists.\n";
        return;
    }

    try {
        if (fs::create_directories(path)) {
            std::cout << "Directory created successfully.\n";
        } else {
            std::cerr << "Error: Failed to create directory.\n";
        }
    } catch (const fs::filesystem_error& e) {
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
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void copyFile(const std::string& sourceDir) {
    std::string filename, destDir;
    std::cout << "Enter the name of the file to copy (e.g., example.txt): ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the full path of the destination directory: ";
    std::getline(std::cin, destDir);

    std::string sourceFilePath = normalizePath(sourceDir + "/" + filename);
    destDir = normalizePath(destDir);

    if (!fs::exists(sourceFilePath) || !fs::is_regular_file(sourceFilePath)) {
        std::cerr << "Error: Source file does not exist or is not a regular file. Checked path: " << sourceFilePath << '\n';
        return;
    }

    if (!fs::exists(destDir)) {
        std::cout << "Destination directory does not exist. Creating it...\n";
        try {
            fs::create_directories(destDir);
            std::cout << "Directory created successfully.\n";
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error creating directory: " << e.what() << '\n';
            return;
        }
    } else if (!fs::is_directory(destDir)) {
        std::cerr << "Error: Destination path is not a directory. Checked path: " << destDir << '\n';
        return;
    }

    std::string destFilePath = normalizePath(destDir + "/" + filename);
    try {
        fs::copy(sourceFilePath, destFilePath, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully to: " << destFilePath << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void moveFile(const std::string& sourceDir) {
    std::string filename, destDir;
    std::cout << "Enter the name of the file to move (e.g., example.txt): ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the full path of the destination directory: ";
    std::getline(std::cin, destDir);

    std::string sourceFilePath = normalizePath(sourceDir + "/" + filename);
    destDir = normalizePath(destDir);

    if (!fs::exists(sourceFilePath) || !fs::is_regular_file(sourceFilePath)) {
        std::cerr << "Error: Source file does not exist or is not a regular file. Checked path: " << sourceFilePath << '\n';
        return;
    }

    if (!fs::exists(destDir)) {
        std::cout << "Destination directory does not exist. Creating it...\n";
        try {
            fs::create_directories(destDir);
            std::cout << "Directory created successfully.\n";
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error creating directory: " << e.what() << '\n';
            return;
        }
    } else if (!fs::is_directory(destDir)) {
        std::cerr << "Error: Destination path is not a directory. Checked path: " << destDir << '\n';
        return;
    }

    std::string destFilePath = normalizePath(destDir + "/" + filename);
    try {
        fs::rename(sourceFilePath, destFilePath);
        std::cout << "File moved successfully to: " << destFilePath << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void viewFile(const std::string& path) {
    std::string filename;
    std::cout << "Enter the name of the file to view (e.g., example.txt): ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    std::string filePath = normalizePath(path + "/" + filename);
    if (!fs::exists(filePath)) {
        std::cerr << "Error: File does not exist. Checked path: " << filePath << '\n';
        return;
    }

    if (!fs::is_regular_file(filePath)) {
        std::cerr << "Error: Path is not a regular file. Checked path: " << filePath << '\n';
        return;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    std::cout << "Contents of " << filePath << ":\n";
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }
    file.close();
}

int main() {
    int choice;

    do {
        displayMainMenu();
        while (!(std::cin >> choice)) {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: openDirectory(); break;
            case 2: createDirectory(); break;
            case 3: std::cout << "Exiting program. Goodbye!\n"; break;
            default: std::cerr << "Invalid choice. Returning to Main Menu.\n"; break;
        }
    } while (choice != 3);

    return 0;
}