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

class StringSerializer {
public:
    std::string fromStream(std::istream& is, std::size_t& size) {
        std::string to;
        char ch = is.get();
        while (!is.eof() && ch != '\n') {
            to.push_back(ch);
            ch = is.get();
        }
        to.shrink_to_fit();
        size = to.size();
        return to;
    }

    void toStream(const std::string& from, std::ostream& os) {
        os << from << '\n';
    }
};

void extSort(int argn, char** args) {
    static struct option long_options[] = {
        {"input",       required_argument,  0,  'i' },
        {"output",      required_argument,  0,  'o' },
        {"temp-dir",    required_argument,  0,  't' },
        {"files-limit", required_argument,  0,  'f' },
        {"memory-limit",required_argument,  0,  'm' },
        {"help",        no_argument,        0,  'h' },
        {0,             0,                  0,   0 }
    };

    std::string input;
    std::string output;
    std::string tempDirectory("/tmp");
    std::size_t filesLimit  = 50;    // 1 << 14;
    std::size_t memoryLimit = 1024;  // 1 << 29;  // 512B

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
            std::cerr << "Usage:\n"
                << " -i, --input : Input file\n"
                << " -o, --output : Output file\n"
                << " -t, --temp-dir : Direcory for temporary files\n"
                << " -f, --files-limit : The maximum number of open files / File Descriptor\n"
                << " -m, --memory-limit : memory limit in bytes\n"
                << " -h, --help : print this help" << std::endl;
            return;
        } else {
            if (0 != opterr) {
                throw ArgparseException();
            }
        }
    };

    TExternalSorter<
        std::string,
        StringSerializer,
        std::less<std::string>
    > sorter(
        std::less<std::string>(),
        StringSerializer(),
        memoryLimit,
        filesLimit,
        tempDirectory
    );

    if (!input.empty()) {
        std::ifstream in(input.c_str(), std::fstream::in);
        if (!output.empty()) {
            std::ofstream out(output.c_str(), std::fstream::out);
            sorter.sort(in, out);
        } else {
            sorter.sort(in, std::cout);
        }
    } else {
        if (!output.empty()) {
            std::ofstream out(output.c_str(), std::fstream::out);
            sorter.sort(std::cin, out);
        } else {
            sorter.sort(std::cin, std::cout);
        }
    }
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
