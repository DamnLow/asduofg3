/*
 * GraphHandler.h
 *
 *  Created on: Jun 11, 2008
 *      Author: zaum
 *     Updated: kuswik, 2016
 */

#ifndef GRAPHHANDLER_H_
#define GRAPHHANDLER_H_

#include "Graph/Element.h"
#include "Graph/Net.h"
#include "Library/ElementInfo.h"
#include <iostream>
#include <memory>
#include <vector>

// forward declarations
class Element;
class Net;
class LibraryHandler;

/**
 * Central interface class to the graph. Used to build up and manipulate
 * the graph as well as to search elements etc.
 */
class GraphHandler {
private:
    std::vector<std::shared_ptr<Element>> sharedElements;
    std::vector<std::shared_ptr<Net>> sharedNets;

    /** List of all element instances.*/
    std::vector<const Element*> elements;

    /** List of all net instances*/
    std::vector<const Net*> nets;

    std::shared_ptr<LibraryHandler> libraryHandler;

    // prevent from using the copy constructor and assignment operator
    GraphHandler(const GraphHandler&) = delete;
    GraphHandler& operator=(const GraphHandler&) = delete;

    /**
     * returns pointer to LibraryHandler.
     */
    LibraryHandler* getLibraryHandler() const;

    /**
     * Creates the element with the given name, if it does not exist.
     * Else returns a reference to the already existing element.
     * Lookup is performed via the element-vector.
     */
    Element* createOrGetElement(const std::string& name, const std::string& type, const ElementInfo* elementInfo);

    /**
     * Creates the net with the given name, if it does not exist.
     * Else returns a reference to the already existing net.
     * Lookup is performed via the net-vector.
     */
    Net* createOrGetNet(const std::string& name);

    /**
     * Creates the element with elementName and create or connect the nets with the
     * names given in the corresponding vectors.
     */
    void createOrGetElementWithNets(const std::string& elementName, const std::string& type, const std::vector<std::string>& inNetNames, const std::string &outNetName, const ElementInfo* elementInfo);

    friend class InternalParser;
    friend class Parser;
    friend class DelayCalculator;

    /**
     * Prints the content of the graph to stdout, for debug purposes only.
     */
    friend std::ostream& operator<<(std::ostream& stream, const GraphHandler& graphHandler);

    /**
     * Returns the Element with given name, for parser only.
     */
    const Element* getElement(const std::string& name) const;

public:
    /**
     * Returns the vector of all Elements.
     */
    const std::vector<const Element*>& getAllElements() const;

    /**
     * Returns the Element with given ID.
     */
    const Element* getElement(const size_t& id) const;

    /**
     * Returns the vector of all Nets.
     */
    const std::vector<const Net*>& getAllNets() const;

    /**
     * Returns the Net with given ID.
     */
    const Net* getNet(const size_t& id) const;

    /**
     * Constructor.
     */
    GraphHandler();
};

#endif /*GRAPHHANDLER_H_*/
