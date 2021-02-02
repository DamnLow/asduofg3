/*
 * Element.h
 *
 *  Created on: Jun 11, 2008
 *      Author: zaum
 *     Updated: kuswik, 2016
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "template.h"
#include <string>
#include <vector>

// forward declarations
class TerminalInfo;
class Net;
class ElementInfo;

/**
 * Class which represents all sequential and combinatorial gates in the graph
 */
class Element {

private:
    std::string name;
    std::vector<const Net*> inNets;
    std::vector<const Net*> outNets;
    /// Represents the position in the elements vector in graphHandler
    size_t id;
    /// A pointer to the corresponding ElementInfo object
    const ElementInfo* elementInfo;

    /// Constructor
    Element(const std::string& name, size_t id, const ElementInfo* elementInfo);
    // prevent from using the default constructor, copy constructor and assignment operator
    Element() = delete;
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;

    /// Link a net to the next free entry in the inNets-vector
    void connectInNet(const Net* inNet);
    /// Link a net to outNet
    void connectOutNet(const Net* outNet);

    friend class GraphHandler;
    friend class Factory;

    /**
     * Prints the content of all members to stdout.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Element& elem);

public:
    /**
     * Returns the ID of this element.
     * this == graphHandler->getAllElements().at(id)
     */
    size_t getId() const;

    /**
     * Returns the name of this Element, for example "C1".
     */
    const std::string& getName() const;

    /**
     * Returns the vector of the incoming Nets.
     */
    const std::vector<const Net*>& getInNets() const;

    /**
     * Returns the vector of the outgoing Nets.
     */
    const std::vector<const Net*>& getOutNets() const;

    /**
     * Returns the corresponding ElementInfo. Can be used to lookup the ElementType of this Element.
     */
    const ElementInfo* getElementInfo() const;
};

#endif /*ELEMENT_H_*/
