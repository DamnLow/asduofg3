/*
 * Parser.h
 *
 *  Created on: Apr 30, 2008
 *      Author: panitz
 *     Updated: kuswik, 2016
 */

#ifndef PARSER_H
#define PARSER_H

class GraphHandler;
class LibraryHandler;

/**
 * Yal-Parser. This class parses *.yal files and imports them into
 * the graph data base. Supported formats: YAL.
 */
class Parser {
public:
    static void parse(int argc, const char** argv, GraphHandler* graphHandler, const int debugLevel = 0);
};

#endif // PARSER_H
