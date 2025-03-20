#pragma once
#include <fstream>
#include <string>
#include <random>
#include <iostream>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

class WordReader {
public:
    // Constructor: Open the file
    WordReader(const std::string& filename);

    // Destructor: Close the file
    ~WordReader();

    // Function to get a random word
    std::string getRandomWord();

private:
    std::ifstream mFile;  // File stream
    std::string mFilename;  // File name
    size_t mFileSize;  // File size for random access

    // Helper function to get the file size
    size_t getFileSize();
};

