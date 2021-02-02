/*
 * main.cpp
 */
 
#include <iostream>
#include <fstream>
#include <string>

#include "Graph/GraphHandler.h"
#include "Parser/Parser.h"
#include "Analysis-EDA/AnalysisEDA.h"

int main(int argc, const char** argv) {
    GraphHandler graphHandler;
    Parser::parse(argc, argv, &graphHandler);
	
    std::vector<std::string> args(argv, argv+argc);
    std::string inFileName("examples/" + args[2] + "_in.csv");
    std::ifstream inputFile;
    std::vector<std::vector<Logic>> inputData;

    inputFile.open(inFileName);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open " << inFileName << std::endl;
    } else {
        std::vector<Logic> inputValues;
        while (inputFile.good()) {
            char value = inputFile.get();
            inputValues.push_back(static_cast<Logic>(value - '0'));
            if (inputFile.get() == '\n') {
                inputData.push_back(inputValues);
                inputValues.clear();
            }
        }
    }
    inputFile.close();

    AnalysisEDA analysisEDA(&graphHandler, inputData);

    analysisEDA.run();

    return 0;
}
