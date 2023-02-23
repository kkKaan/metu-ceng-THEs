#include "the8.h"
#include <fstream>
#include <sstream>
#include <string>

namespace {
struct Params {
    std::string sequence;
    std::pair<std::string,std::string> mapping;
    std::string pattern;
};

// Reads .test files and fills a `Params` struct.
// .test file consists of following items. Each element in the below list is on
// their separate lines.
//
// <sequence>
// <mapping(symbol, symbol)>
// <pattern>

Params ReadTestCase(std::string filename) {
    Params params;
    std::ifstream ftest(filename);
    if (ftest.fail()) {
        std::cerr << "[X] Error opening test file! Exiting.\n";
        exit(1);
    }
    try {
        std::string line;
        std::getline(ftest, line);
        std::istringstream iss(line);
        iss >> params.sequence;
        
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        std::string s1, s2;
        iss >> s1 >> s2;
        params.mapping = std::make_pair(s1,s2);
    
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        iss >> params.pattern;
    
    } catch (...) {
        std::cerr << "[X] Error reading test file! Exiting.\n";
        exit(2);
    }
    return params;
}

} // namespace

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s file\n", argv[0]);
        printf("arguments:\n  file:\tPath to the input file.\n");
        exit(0);
  }
    auto p = ReadTestCase(argv[1]);
    matchPattern(p.sequence, p.mapping, p.pattern);
    return 0;
}
