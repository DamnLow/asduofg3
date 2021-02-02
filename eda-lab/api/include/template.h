/*
 * template.h
 *
 *  Created on: Apr 30, 2008
 *      Author: panitz
 *     Updated: kuswik, 2016
 */

// Purpose: This file contains template instantions and declaration of
//          constants which are used in more than one file.

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include <cassert>
#include <ostream>

// COORDINATES
typedef std::pair<int, int> Coord;

// YAL INFORMATION
enum class PortType {
    Unknown,
    Input,  //!< Input terminal
    Output, //!< Output terminal
    Bidi,
    Feedthrough
};

inline std::ostream& operator<<(std::ostream& o, const PortType p) {
    switch (p) {
    case PortType::Unknown:
        return o << "UnknownPortType";
    case PortType::Input:
        return o << "InputPortType";
    case PortType::Output:
        return o << "OutputPortType";
    case PortType::Bidi:
        return o << "BidiPortType";
    case PortType::Feedthrough:
        return o << "FeedthroughPortType";
    default:
        assert(false);
        break;
    }
}

//LOGIC INFORMATION
enum class Logic {
    logic0 = 0,
    logic1 = 1,
    logicX = 2,
    logicD = 3,
    logicNotD = 4,
    logicError = 5
};

inline size_t toIndex(Logic l) {
    return static_cast<size_t>(l);
}

inline std::ostream& operator<<(std::ostream& o, const Logic l) {
    switch (l) {
    case Logic::logic0:
        return o << "logic0";
    case Logic::logic1:
        return o << "logic1";
    case Logic::logicX:
        return o << "logicX";
    case Logic::logicD:
        return o << "logicD";
    case Logic::logicNotD:
        return o << "logicNotD";
    case Logic::logicError:
        return o << "logicError";
    default:
        assert(false);
        break;
    }
}

//ELEMENT INFORMATION
enum class ElementType {
    Not, //!< NOT gate
    And, //!< AND2 gate
    Or,  //!< OR2 gate
    Dff, //!< D-Flip-Flop
    TopLevelCell, //!< Circuit
    Unknown
};

inline std::ostream& operator<<(std::ostream& o, const ElementType e) {
    switch (e) {
    case ElementType::Not:
        return o << "NOT";
    case ElementType::And:
        return o << "AND2";
    case ElementType::Or:
        return o << "OR2";
    case ElementType::Dff:
        return o << "DFF";
    case ElementType::TopLevelCell:
        return o << "CIRCUIT";
    case ElementType::Unknown:
        return o << "UNKNOWN";
    default:
        assert(false);
        break;
    }
}

#endif /*TEMPLATE_H_*/
