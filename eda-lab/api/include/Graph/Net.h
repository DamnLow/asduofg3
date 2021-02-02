/*
 * Net.h
 *
 *  Created on: Jun 11, 2008
 *      Author: zaum
 *     Updated: kuswik, 2016
 */

#ifndef NET_H_
#define NET_H_

#include <string>
#include <vector>

// forward declarations
class Element;

/**
 * Class to represent nets in graph
 */
class Net {
private:
    std::string name;
    const Element* inElement;
    std::vector<const Element*> outElements;
    size_t id;

    /// Constructor
    Net(const std::string& name, size_t id);
    // prevent from using the default constructor, copy constructor and assignment operator
    Net() = delete;
    Net(const Net&) = delete;
    Net& operator=(const Net&) = delete;

    /// Link a Element to inElement
    void connectInElement(const Element* inElement);
    /// Link a Element to the next free entry in the outElements-vector
    void connectOutElement(const Element* outElement);

    friend class GraphHandler;
    friend class Factory;
    friend class InternalParser;

    /**
     * Prints the content of all members to stdout.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Net& net);

public:
    /**
     * Returns the ID of this net.
     * this == graphHandler->getAllNets().at(id)
     */
    size_t getId() const;

    /**
     * Returns the name of this Net, for example "S001".
     */
    const std::string& getName() const;

    /**
     * Returns the incoming Element. Primary inputs do not have an inElement. Returns nullptr in that case.
     */
    const Element* getInElement() const;

    /**
     * Returns the vector of outgoing Elements. Primary outputs are marked by nullptr-Elements in this vector.
     */
    const std::vector<const Element*>& getOutElements() const;
};

#endif /*NET_H_*/
