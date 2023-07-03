#include "the7.h"
#include <fstream>
#include <sstream>
#include <string>

namespace {
struct Params {
    int l;
    int n;
    std::vector<Road> roads;
    int s, d, x, y;
    int printPath;
};

// Reads .test files and fills a `Params` struct.
// .test file consists of following items. Each element in the below list is on
// their separate lines.
//
// <time-until-final(L)>
// <number-of-buildings(N)>
// <cat-building-id(S)> <exam-building-id(D)>
// <printer-building-id(X)> <dorm-building-id(Y)>
// <number-of-roads(M)>
// <building#1> <building#2> <time>  <-- Repeats m times
Params ReadTestCase(std::string filename) {
    Params params;
    params.n = 0;
    params.roads.clear();
    std::ifstream ftest(filename);
    if (ftest.fail()) {
        std::cerr << "[X] Error opening test file! Exiting.\n";
        exit(1);
    }
    try {
        std::string line;
        std::getline(ftest, line);
        std::istringstream iss(line);
        iss >> params.l;
        
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        iss >> params.n;
    
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        iss >> params.s >> params.d;
    
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        iss >> params.x >> params.y;
    
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        int m;
        iss >> m;
        iss.clear();
        params.roads.reserve(m);
        for (int i = 0; i < m; i++) {
            std::getline(ftest, line);
            std::istringstream iss(line);
            int u, v, w;
            iss >> u >> v >> w;
            params.roads.push_back(Road({u, v}, w));
        }
        std::getline(ftest, line);
        iss.clear();
        iss = std::istringstream(line);
        iss >> params.printPath;

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
    CanCatch(p.n, p.roads, p.s, p.d, p.x, p.y, p.l, p.printPath);
    return 0;
}
