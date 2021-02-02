/*
 * Timing.h
 *
 *  Created on: Jun 24, 2009
 *      Author: hoelldam
 *     Updated: kuswik 2016
 */

#ifndef TIMING_H_
#define TIMING_H_

#include <ostream>
#include <cassert>

/**
 * Type definition used as time by all STA implementations.
 */
using Time = float;

/**
 * Enumeration representing rising and falling signal transitions.
 */
enum class TransitionType {
    Rise = 0, //!< Rising transition
    Fall = 1  //!< Falling transition
};

inline std::ostream& operator<<(std::ostream& o, const TransitionType t) {
    switch (t) {
    case TransitionType::Rise:
        return o << "RiseTransitionType";
        break;
    case TransitionType::Fall:
        return o << "FallTransitionType";
        break;
    default:
        assert(false);
        break;
    }
}

#endif /* TIMING_H_ */
