/**
 * @file TapeVisualizer.h
 * @brief Defines the TapeVisualizer class for visualizing Turing machine tapes.
 *
 * This file contains the definition of the TapeVisualizer class, which is used to create
 * visual representations of Turing machine tapes using Graphviz.
 */
#ifndef TURING_MACHINE_TAPEVISUALIZER_H
#define TURING_MACHINE_TAPEVISUALIZER_H


#include <string>
/**
 * @class TapeVisualizer
 * @brief Class for visualizing the tape of a Turing machine using Graphviz.
 *
 * TapeVisualizer reads the contents of a Turing machine's tape from a file and generates
 * a Graphviz (.dot) file that visually represents the tape. It is useful for debugging
 * and understanding the behavior of Turing machines.
 */
class TapeVisualizer {
public:
    /**
     * @brief Constructor for TapeVisualizer.
     *
     * Initializes the TapeVisualizer with a file path to the tape's content. This path
     * is used to read the tape's content for visualization.
     *
     * @param tapeFilePath Path to the file containing the tape's content.
     */
    explicit TapeVisualizer(const std::string& tapeFilePath);
    /**
     * @brief Generates a Graphviz (.dot) file from the tape's content.
     *
     * Creates a visual representation of the tape in Graphviz format and writes it to
     * the specified output file. This method is responsible for reading the tape's content
     * and translating it into a graphical format.
     *
     * @param outputFilePath Path where the Graphviz file will be saved.
     * @throws std::runtime_error if file operations fail.
     */
    void generateGraphvizFile(const std::string& outputFilePath) const;

private:
    std::string tapeFilePath;
};



#endif //TURING_MACHINE_TAPEVISUALIZER_H
