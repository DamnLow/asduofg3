/*
 * TerminalInfo.cpp
 *
 *  Created on: Jun 23, 2008
 *      Author: panitz
 *     Updated: kuswik, 2016
 */

#ifndef TERMINALINFO_H_
#define TERMINALINFO_H_

#include "template.h"

#include <string>

/**
 * Stores Information concerning the terminals of an element.
 * Example: input or output terminal
 */
class TerminalInfo
{
private:
    // Port name
    std::string name;
    // Port type
    PortType type;
    // Port id
    size_t position;
    friend class InternalParser;
    friend class ElementInfo;

    // prevent from using the copy constructor and the assignment operator
    TerminalInfo(const TerminalInfo&) = delete;
    TerminalInfo& operator=(const TerminalInfo&) = delete;

    /**
     * Constructor
     */
    TerminalInfo(const std::string& name, PortType type, Coord lowerLeft, Coord upperRight);

    /// Set the Id of the terminal
    void setPosition(size_t pos);

public:
    /**
     * Returns the name of this Terminal.
     */
    const std::string& getName() const;

    /**
     * Returns the PortType of this Terminal.
     */
    PortType getType() const;

    /**
     * Returns the Position of this Terminal.
     * this == ElementInfo->getInputTerminalInfos().at(position) for Input-Terminals
     * this == ElementInfo->getOutputTerminalInfos().at(position) for OutputTerminals
     */
    size_t getPosition() const;
};
#endif /*TERMINALINFO_H_*/
