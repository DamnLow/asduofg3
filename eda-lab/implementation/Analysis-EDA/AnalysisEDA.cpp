/*
 * AnalysisEDA.cpp
 *
 * This file contains the implementation of the simulator.
 */

#include "AnalysisEDA.h"
#include "Graph/GraphHandler.h"
#include <iostream>

void AnalysisEDA::run() {
    //std::cout << __PRETTY_FUNCTION__ << " is not implemented!" << std::endl;
    // Todo: Implement the simulator here

    //test for git
    // Iterate all elements:
    for (const Element* element : graphHandler->getAllElements()) {
        std::cout << element->getName() << std::endl;
    }

    // Iterate all nets:
    for(const Net* net: graphHandler->getAllNets()) {
        std::cout << net->getName();
        if (net->getInElement() == nullptr)
            std::cout << " (primary input)";
        if (net->getOutElements()[0] == nullptr)
            std::cout << " (primary output)";
        std::cout << std::endl;
    }

    // Iterate all time steps:
    for (const std::vector<Logic>& timeStep : inputData) {
        for (const Logic& value : timeStep) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

#if false
    /*
     * The following code shows some exemplary usage of the API
     */

    // Iterate all elements:
    for (const Element* element : graphHandler->getAllElements()) {
        std::cout << element->getName() << std::endl;
    }

    // Iterate all nets:
    for(const Net* net: graphHandler->getAllNets()) {
        std::cout << net->getName();
        if (net->getInElement() == nullptr)
            std::cout << " (primary input)";
        if (net->getOutElements()[0] == nullptr)
            std::cout << " (primary output)";
        std::cout << std::endl;
    }

    // Iterate all time steps:
    for (const std::vector<Logic>& timeStep : inputData) {
        for (const Logic& value : timeStep) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
#endif
}
