/* 106X Winter 2017 Assignment3
 * Part two
 */

#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"
#include "random.h"
using namespace std;

void loadGrammar(istream & input, Map<string, Vector<string> > & grammarMap);
void recursiveGrammarGenerate(Map<string, Vector<string> > & grammarMap,
				string symbol, string & result);


Vector<string> grammarGenerate(istream& input, string symbol, int times) {
  Vector<string> result;

  Map<string, Vector<string> > grammarMap;
  loadGrammar(input, grammarMap);

  if (symbol == "") {
    throw "Initial symbol can't be empty";
  } else if (!grammarMap.containsKey(symbol)) {
    result.add(symbol);
    cout << "You passed something that can't be expanded" << endl;
    return result;
  } else {
    for (int i = 0; i < times; i++) {
      string s;
      recursiveGrammarGenerate(grammarMap, symbol, s);
      result.add(s);
    }
    return result;
  }
}


/* Function: loadGrammar
 * Usage:    loadGrammar(input, grammarMap)
 * -----------------------------------------
 * Helper function to load grammar txt file
 * into a data structure, which is a map of string
 * to a vector of strings.
 * Parameters and return values:
 * Precondition:
 * Postcondition:
 * Assumption:
 */
void loadGrammar(istream & input, Map<string, Vector<string> > & grammarMap) {
  string line;

  while (true) {
    getline(input, line);
    if (input.fail()) {
      break;
    }

    // split line by "::=" first
    Vector<string> firstSplit = stringSplit(line, "::=");
    string left = firstSplit[0]; // nonterminal, key
    string right = firstSplit[1];

    // split the right side of "::=" by "|"
    Vector<string> secondSplit = stringSplit(right, "|");

    if (grammarMap.containsKey(left)) {
      throw "duplicate keys";
    } else {
      grammarMap.put(left, secondSplit);
    }
  }
}


/* Function: recursiveGrammarGenerate
 * Usage:    string s = recursiveGrammarGenerate(grammarMap, symbol)
 * --------------------------------------------------------------------------------
 * Generates a setence randomly according to the given grammar and starting symbol
 * Parameters and return values:
 * Precondition:
 * Postcondition:
 * Assumptions:
 */
void recursiveGrammarGenerate(Map<string, Vector<string> > & grammarMap,
			      string symbol, string & result) {
  if (!grammarMap.containsKey(symbol)) {
    result += symbol;
    result += " ";
  } else {
    Vector<string> current = grammarMap.get(symbol);
    int rand = randomInteger(0, current.size() - 1);
    string s = current[rand];
    Vector<string> splitString = stringSplit(s, " ");
    for (int i = 0; i < splitString.size(); i++) {
      recursiveGrammarGenerate(grammarMap, splitString[i], result);
    }
  }
}
