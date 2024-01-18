#include <fstream>
#include <sstream>
#include <string>
#include "TapeVisualizer.h"
#include <stdexcept>

TapeVisualizer::TapeVisualizer(const std::string& tapeFilePath) : tapeFilePath(tapeFilePath) {}

void TapeVisualizer::generateGraphvizFile(const std::string& outputFilePath) const {
    std::ifstream tapeFile(tapeFilePath);
    std::ofstream outFile(outputFilePath);

    if (!tapeFile.is_open() || !outFile.is_open()) {
        throw std::runtime_error("Error opening files.");
    }

    std::string tapeContent;
    std::getline(tapeFile, tapeContent);

    outFile << "digraph G {\n";
    outFile << "    rankdir=LR;\n"; // Ensure horizontal layout
    outFile << "    node [shape=record];\n";
    outFile << "    edge [color=white, arrowsize=0.01];\n"; // Set edge color to white and make arrows very small

    std::stringstream ss(tapeContent);
    char symbol;
    int index = 0;

    while (ss >> std::noskipws >> symbol) {
        std::string label;
        if (symbol == '>') {
            label = "&#9658;"; // right-pointing triangle
        } else if (symbol == ' ') {
            label = " "; // Space symbol
        } else {
            label = std::string(1, symbol);
        }

        outFile << "    node" << index << " [label=\"" << label << "\"];\n";
        if (index > 0) {
            outFile << "    node" << (index - 1) << " -> node" << index << ";\n";
        }
        ++index;
    }

    outFile << "}\n";

    tapeFile.close();
    outFile.close();
}
