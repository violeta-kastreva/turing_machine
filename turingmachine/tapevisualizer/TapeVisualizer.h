#ifndef TURING_MACHINE_TAPEVISUALIZER_H
#define TURING_MACHINE_TAPEVISUALIZER_H


#include <string>

class TapeVisualizer {
public:

    explicit TapeVisualizer(const std::string& tapeFilePath);

    void generateGraphvizFile(const std::string& outputFilePath) const;

private:
    std::string tapeFilePath;
};



#endif //TURING_MACHINE_TAPEVISUALIZER_H
