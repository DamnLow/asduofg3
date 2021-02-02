/*
 * ElementInfo.h
 *
 *  Created on: Jun 18, 2008
 *      Author: zaum
 *     Updated: kuswik, 2016
 */

#ifndef ELEMENTINFO_H_
#define ELEMENTINFO_H_

#include "template.h"

#include <string>
#include <vector>
#include <memory>

// forward declarations
class TerminalInfo;

/**
 * Stores Information concerning the type of an element. Example:
 * The element type is connected to element specific data like
 * inputs and outputs, etc.
 */
class ElementInfo {
private:
    /**Element Type.*/
    ElementType elementType;
    /**Vector of terminals to the element.*/
    std::vector<std::shared_ptr<TerminalInfo>> sharedTerminals;

    std::vector<const TerminalInfo*> inputTerminals;
    std::vector<const TerminalInfo*> outputTerminals;

    /// Constructor
    ElementInfo(const ElementType& elementType, int width, int height);
    // prevent from using the default constructor, copy constructor and the assignment operator
    ElementInfo();
    ElementInfo(const ElementInfo&);
    ElementInfo& operator=(const ElementInfo&);

    /**
     * Add a TerminalInfo object to the terms vector.
     */
    void addTerminalInfo(TerminalInfo* terminalInfo);

    /**
     * Returns the TerminalInfo at the given position.
     */
    const TerminalInfo* getTerminalInfo(const size_t pos) const;

    friend class ElementBuilder;
    friend class LibraryHandler;
    friend class InternalParser;

    /**
     * Print the content of all members to stdout.
     */
    friend std::ostream& operator<<(std::ostream& stream, const ElementInfo* elemInfo);

public:

    /**
     * Returns the ElementType of corresponding Elements, for example ElementType::And.
     */
    ElementType getType() const;

    /**
     * Returns the vector of Input-TerminalInfos.
     */
    const std::vector<const TerminalInfo*>& getInputTerminalInfos() const;

    /**
     * Returns the vector of Output-TerminalInfos.
     */
    const std::vector<const TerminalInfo*>& getOutputTerminalInfos() const;
};

#endif /*ELEMENTINFO_H_*/
