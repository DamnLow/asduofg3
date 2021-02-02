/*
 * DelayCalculator.h
 *
 *  Created on: Oct 9, 2009
 *      Author: hoelldam
 *     Updated: kuswik, 2016
 */

#ifndef DELAYCALCULATOR_H_
#define DELAYCALCULATOR_H_

#include "Timing.h"

// forward declarations
class Element;
class GraphHandler;
class LibraryHandler;
class Net;

/**
 * Calculates all interconnect and gate delays as well as register constraints.
 */
class DelayCalculator {
public:
    /**
     * Determines the clock period of the current circuit.
     * @return the clock period.
     */
    Time getClockPeriod() const;

    /**
     * Calculates the interconnect delay within the given net (the clock delay for the clock-net).
     * @param netId ID of the net, e.g. 0.
     * @param toElementPos Position of the toElement in the outElements vector from net,
     *                     in case of primary output use position of the nullptr in that vector.
     * @param Transition TransitionType of the net (TransitionType::Rise or TransitionType::Fall).
     * @return The calculated interconnect delay.
     */
    Time calcNetDelay(size_t netId, size_t toElementPos, TransitionType transition) const;

    /**
     * Calculates the gate delay within the given combinatorial element.
     * @param elementId ID of the element, e.g. 0.
     * @param TerminalInPos Position of the input terminal of the element.
     * @param fromTransition TransitionType at the inNet (TransitionType::Rise or TransitionType::Fall).
     * @param toTransition TransitionType at the outNet (TransitionType::Rise or TransitionType::Fall).
     * @return The calculated gate delay. The delay for D-flip-flops is between the CLK and Q terminals.
     */
    Time calcElementDelay(size_t elementId, size_t TerminalInPos,
                          TransitionType fromTransition, TransitionType toTransition) const;
    /**
     * Calculates the setup time of all D-flip-flops.
     * @param transition TransitionType (TransitionType::Rise or TransitionType::Fall).
     * @return The calculated setup time
     */
    Time calcSetupTime(TransitionType transition) const;

    /**
     * Calculates the hold time of all D-flip-flops.
     * @param transition TransitionType (TransitionType::Rise or TransitionType::Fall).
     * @return The calculated hold time
     */
    Time calcHoldTime(TransitionType transition) const;

    /**
     * Constructor.
     * @param graphHandler GraphHandler with all netlist elements and nets.
     */
    DelayCalculator(const GraphHandler* graphHandler);
    ~DelayCalculator();

private:
    const GraphHandler* graphHandler;

    // prevent from using the default constructor, copy constructor and assignment operator
    DelayCalculator() = delete;
    DelayCalculator(const DelayCalculator&) = delete;
    DelayCalculator& operator=(const DelayCalculator&) = delete;

};

#endif /* DELAYCALCULATOR_H_ */
