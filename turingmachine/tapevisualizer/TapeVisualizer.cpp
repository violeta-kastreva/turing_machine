#include <fstream>
#include <sstream>
#include <string>
#include "TapeVisualizer.h"

TapeVisualizer::TapeVisualizer(const std::string& tapeFilePath) : tapeFilePath(tapeFilePath) {}

void TapeVisualizer::generateGraphvizFile(const std::string& outputFilePath) const {
    std::ifstream tapeFile(tapeFilePath);
    std::ofstream outFile(outputFilePath);

    if (!tapeFile.is_open() || !outFile.is_open()) {
        throw std::runtime_error("Error opening files.");
    }

    // Implementation of the Graphviz file generation logic...
    std::string tapeContent;
    std::getline(tapeFile, tapeContent);
    // ... (rest of the visualization logic)

    outFile << "digraph G {\n";
    outFile << "    rankdir=LR;\n";
    outFile << "    node [shape=record];\n";

    std::stringstream ss(tapeContent);
    char symbol;
    int index = 0;

    while (ss >> symbol) {
        outFile << "    node" << index << " [label=\"<f0> " << symbol << "\"];\n";
        if (index > 0) {
            outFile << "    node" << (index - 1) << " -> node" << index << ";\n";
        }
        ++index;
    }

    outFile << "}\n";

    tapeFile.close();
    outFile.close();
}
