#include "WordReader.h"

// Constructor: Open the file in binary mode
WordReader::WordReader(const std::string& filename) : mFilename(filename) {
    mFile.open(filename, std::ios::in | std::ios::binary);  // Open file in binary mode
    if (!mFile.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + filename);
    }

    // Get the size of the file
    mFileSize = getFileSize();
}

// Destructor: Close the file when done
WordReader::~WordReader() {
    if (mFile.is_open()) {
        mFile.close();
    }
}

// Helper function to get the file size
size_t WordReader::getFileSize() {
    mFile.seekg(0, std::ios::end);  // Move to the end of the file
    size_t size = static_cast<size_t>(mFile.tellg());  // Get the current position (size)
    mFile.seekg(0, std::ios::beg);  // Move back to the beginning of the file
    return size;
}

// Function to retrieve a random word from the file
std::string WordReader::getRandomWord() {
    if (!mFile.is_open()) {
        throw std::ios_base::failure("File is not open");
    }

    // Generate a random byte position in the file
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, mFileSize - 1);
    size_t randomPos = dist(gen);

    // Go to the random position
    mFile.seekg(randomPos);

    // Backtrack to the start of the word (or the beginning of the line)
    char ch;
    while (mFile.get(ch)) {
        if (ch == '\n' || mFile.tellg() == randomPos) {
            break;
        }
        randomPos--;
    }

    // Now that we are at the beginning of the word, get it
    std::string word;
    std::getline(mFile, word);
    return word;
}
