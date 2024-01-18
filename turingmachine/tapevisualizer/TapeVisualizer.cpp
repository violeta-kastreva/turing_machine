#include <fstream>
#include <sstream>
#include <string>
#include "TapeVisualizer.h"
#include <stdexcept>
/**
 * @brief Constructor for TapeVisualizer.
 *
 * Initializes the TapeVisualizer with the provided file path to the tape's content.
 *
 * @param tapeFilePath Path to the file containing the tape's content.
 */
TapeVisualizer::TapeVisualizer(const std::string& tapeFilePath) : tapeFilePath(tapeFilePath) {}

/**
 * @brief Generates a Graphviz (.dot) file from the tape's content.
 *
 * Reads the tape content from the provided file and creates a Graphviz representation
 * of the tape. This includes creating nodes for each symbol on the tape and
 * connecting them in order. Special handling is provided for the tape's head symbol
 * (represented by '>'), which is visualized as a right-pointing triangle.
 *
 * @param outputFilePath Path where the Graphviz file will be saved.
 * @throws std::runtime_error if file operations fail.
 */
void TapeVisualizer::generateGraphvizFile(const std::string& outputFilePath) const {
    std::ifstream tapeFile(tapeFilePath);
    std::ofstream outFile(outputFilePath);

    if (!tapeFile.is_open() || !outFile.is_open()) {
        throw std::runtime_error("Error opening files.");
    }

    std::string tapeContent;
    std::getline(tapeFile, tapeContent);

    outFile << "digraph G {\n";
    outFile << "    rankdir=LR;\n";
    outFile << "    node [shape=record];\n";

    std::stringstream ss(tapeContent);
    char symbol;
    int index = 0;

    while (ss >> symbol) {
        std::string label;
        if (symbol == '>') {
            label = "&#9658;"; // right-pointing triangle
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
