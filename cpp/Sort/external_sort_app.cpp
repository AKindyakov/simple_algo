#include <cstring>
#include <functional>
#include <iostream>
#include <string>

#include "getopt.h"

#include "external_sort.h"

class ArgparseException: public std::exception {
public:
    ArgparseException() {}
    ArgparseException(const std::string& what) {
        whatHappen.append(what);
    }

    template<typename T>
    ArgparseException& operator<<(const T& val) {
        std::ostringstream ostr;
        ostr << val;
        whatHappen.append(ostr.str());
        return *this;
    }

    const char* what() const throw() override { return whatHappen.c_str(); }

private:
    std::string whatHappen = "[argument parser exception] ";
};

int extSort(int argn, char** args) {
    static struct option long_options[] = {
        {"input",       required_argument,  0,  'i' },
        {"output",      required_argument,  0,  'o' },
        {"temp-dir",    required_argument,  0,  't' },
        {"files-limit", required_argument,  0,  'f' },
        {"memory-limit",required_argument,  0,  'm' },
        {"help",        required_argument,  0,  'h' },
        {0,             0,                  0,   0 }
    };

    std::string input;
    std::string output;
    std::string tempDirectory("/tmp");
    std::size_t filesLimit  = 1024;
    std::size_t memoryLimit = 1 << 29;  // 512B

    int option_index = 0;
    while (int c =
        getopt_long(argn, args, "i:o:t:f:m:?:h", long_options, &option_index)
    ) {
        if (c == -1) {
            break;
        } else if (c == 'i') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'i\'");
            }
            input = optarg;
        } else if (c == 'o') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'o\'");
            }
            output = optarg;
        } else if (c == 't') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'t\'");
            }
            tempDirectory = optarg;
        } else if (c == 'f') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'f\'");
            }
            filesLimit = std::stoul(optarg);
        } else if (c == 'm') {
            if (!optarg) {
                throw ArgparseException("empty value for option \'m\'");
            }
            memoryLimit = std::stoul(optarg);
        } else if (c == 'h') {
            std::cerr << "Usage will be here" << std::endl;
        } else {
            if (0 != opterr) {
                throw ArgparseException();
            }
        }
    };


    TExternalSorter<std::string, std::less<std::string>> sorter(
        std::less<std::string>(),
        memoryLimit,
        filesLimit,
        tempDirectory.c_str()
    );

    sorter.sort(input.c_str(), output.c_str());
    return 0;
}

int main(int argn, char** args) {
    try {
        extSort(argn, args);
    } catch (const std::exception& except) {
        std::cerr << except.what() << std::endl;
        return 1;
    }
    return 0;
}
