/*
 * AnalysisEDA.cpp
 *
 * This file contains the implementation of the simulator.
 */

#include "AnalysisEDA.h"
#include "Graph/GraphHandler.h"
#include <iostream>

void AnalysisEDA::run() {
    size_t num_elements = graphHandler->getAllElements().size();

    // output values of the elements in the previous time step
    std::vector<Logic> prev_out(num_elements, Logic::logicX);

    // all elements of the graph will be sorted here in a pseudotopological sort
    std::vector<const Element*> all_elements;

    // cachebuffer vector during the pseudotopological sort
    // will be used as a queue
    std::vector<const Element*> free_elements;

    // Contains the number of inputs of each element.
    // Primary inputs will be counted as zero.
    std::vector<int> top_in_degree(num_elements);

    // Initiates the top_in_degree vector for the pseudotopological sort.
    // Flip-Flops will be evaluated as primary inputs.
    for (const Element* element : graphHandler->getAllElements()) {
        int degree = 0;

        for (const Net* net : element->getInNets()) {
            const Element* input_element = net->getInElement();
            if (input_element && input_element->getElementInfo()->getType() != ElementType::Dff) {
                degree++;
            }
        }

        if (degree) {
            top_in_degree[element->getId()] = degree;
        } else {
            free_elements.push_back(element);
        }
    }

    // The loop performs a pseudotopological sort to order the elements
    // in flow direction of the signals from the inputs to the outputs.
    while (free_elements.size()) {
        const Element* element = free_elements.front();
        free_elements.erase(free_elements.begin());
        all_elements.push_back(element);

        for (const Net* net : element->getOutNets()) {
            for (const Element* output_element : net->getOutElements()) {
                if (output_element && !--top_in_degree[output_element->getId()]) {
                    free_elements.push_back(output_element);
                }
            }
        }
    }

    /*
    for (const Element* element : all_elements) {
        std::cout << "(" << element->getName() << ", " << element->getElementInfo()->getType() << ") ";
    }
    std::cout << std::endl;
    */

    // iterate over each time step
    for (const std::vector<Logic>& timeStep : inputData) {

        // output values of the elements in the current time step
        std::vector<Logic> cur_out(num_elements, Logic::logicX);

        /*
        for (const Logic& value : timeStep) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        */

        // Calculates the output of each element.
        for (const Element* element : all_elements) {
            size_t element_id = element->getId();

            // input values of the element
            std::vector<Logic> input;

            // buffer variable
            Logic out = Logic::logicX;

            // Calculates the input values of the element.
            for (const Net* net : element->getInNets()) {

                // the upstream element of the current net
                const Element* input_element = net->getInElement();

                // Connected with one or more logic gates
                if (input_element) {

                    // differ between a Flip Flop and an
                    // usual logic gate (NOT, AND, OR ...)
                    std::vector<Logic> output = input_element->getElementInfo()->getType() == ElementType::Dff ? prev_out : cur_out;

                    // Get input value from upstream element.
                    input.push_back(output[input_element->getId()]);

                // Connected with a primary input
                } else {
                    std::string net_name = net->getName();

                    // Get input value from primary input.
                    if (net_name.compare("CLOCK")) {
                        size_t pos;
                        std::sscanf(net_name.substr(1).c_str(), "%zu", &pos);
                        input.push_back(timeStep[--pos]);

                    // Get input value from the clock
                    } else {
                        input.insert(input.begin(), timeStep.back());
                    }
                }
            }

            // identify type of the element
            switch (element->getElementInfo()->getType()) {
            case ElementType::Not:

                // invert input if clearly known, else let input through
                switch (input[0]) {
                case Logic::logic0:
                    out = Logic::logic1;
                    break;
                case Logic::logic1:
                    out = Logic::logic0;
                    break;
                case Logic::logicD:
                    out = Logic::logicNotD;
                    break;
                case Logic::logicNotD:
                    out = Logic::logicD;
                    break;
                default:
                    out = input[0];
                    break;
                }
                break;
            case ElementType::And:
                out = Logic::logic1;

                // check for D and notD
                for (Logic value : input) {
                    if (value == Logic::logicD || value == Logic::logicNotD) {
                        out = value;
                        Logic counterpart = value == Logic::logicD ? Logic::logicNotD : Logic::logicD;
                        for (Logic value_counterpart : input) {
                            if (value_counterpart == counterpart) {
                                out = Logic::logic0;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (out != Logic::logic0) {

                    // check for X
                    for (Logic value : input) {
                        if (value == Logic::logicX) {
                            out = Logic::logicX;
                            break;
                        }
                    }

                    // check for 0
                    for (Logic value : input) {
                        if (value == Logic::logic0) {
                            out = value;
                            break;
                        }
                    }
                }

                // check for error
                for (Logic value : input) {
                    if (value == Logic::logicError) {
                        out = value;
                        break;
                    }
                }
                break;
            case ElementType::Or:
                out = Logic::logic0;

                // check for D and notD
                for (Logic value : input) {
                    if (value == Logic::logicD || value == Logic::logicNotD) {
                        out = value;
                        Logic counterpart = value == Logic::logicD ? Logic::logicNotD : Logic::logicD;
                        for (Logic value_counterpart : input) {
                            if (value_counterpart == counterpart) {
                                out = Logic::logic1;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (out != Logic::logic1) {

                    // check for X
                    for (Logic value : input) {
                        if (value == Logic::logicX) {
                            out = value;
                            break;
                        }
                    }

                    // check for 1
                    for (Logic value : input) {
                        if (value == Logic::logic1) {
                            out = value;
                            break;
                        }
                    }
                }

                // check for error
                for (Logic value : input) {
                    if (value == Logic::logicError) {
                        out = value;
                        break;
                    }
                }
                break;
            case ElementType::Dff:
                out = prev_out[element_id];

                // clock signal enabled
                if (input[0] == Logic::logic1) {

                    // Directs input value to the output.
                    prev_out[element_id] = input[1];
                }
                break;
            default:
                break;
            }
            cur_out[element_id] = out;
        }

        // Prints the primary outputs to the shell.
        for (const Net* net : graphHandler->getAllNets()) {
            if (!net->getOutElements()[0]) {
                std::cout << cur_out[net->getInElement()->getId()] << " ";
            }
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
