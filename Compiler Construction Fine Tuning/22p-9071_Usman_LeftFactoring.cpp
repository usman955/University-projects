#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

// Helper: trim leading and trailing spaces
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == string::npos || end == string::npos) return "";
    return str.substr(start, end - start + 1);
}

// Helper: return ε if empty
string handleEpsilon(const string& prod) {
    return prod.empty() ? "ε" : prod;
}

// Splits a production string into individual alternatives
vector<string> splitProductions(const string& productionStr) {
    vector<string> result;
    stringstream ss(productionStr);
    string part;
    while (getline(ss, part, '|')) {
        result.push_back(trim(part));
    }
    return result;
}

// Returns the common prefix of two strings
string commonPrefix(const string& a, const string& b) {
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    return a.substr(0, i);
}

// Read CFG file
void readCFG(const string& filename, map<string, vector<string>>& grammar) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string nonTerminal, arrow;
        ss >> nonTerminal >> arrow;
        string productions;
        getline(ss, productions);
        vector<string> split = splitProductions(productions);
        grammar[nonTerminal] = split;
    }

    file.close();
}

// Write CFG file
void writeCFG(const string& filename, const map<string, vector<string>>& grammar) {
    ofstream file(filename);
    for (const auto& rule : grammar) {
        file << rule.first << " -> ";
        for (size_t i = 0; i < rule.second.size(); ++i) {
            file << rule.second[i];
            if (i != rule.second.size() - 1) file << " | ";
        }
        file << endl;
    }
    file.close();
}

// Perform left factoring
void leftFactor(map<string, vector<string>>& grammar) {
    map<string, vector<string>> newGrammar;
    int counter = 1;

    for (const auto& [nonTerminal, productions] : grammar) {
        map<string, vector<string>> prefixGroups;
        for (const string& prod : productions) {
            string key = prod.substr(0, 1);  // group by first character
            prefixGroups[key].push_back(prod);
        }

        bool factored = false;

        for (const auto& [prefix, group] : prefixGroups) {
            if (group.size() > 1) {
                // Find the longest common prefix in the group
                string currentPrefix = group[0];
                for (size_t i = 1; i < group.size(); ++i)
                    currentPrefix = commonPrefix(currentPrefix, group[i]);

                if (!currentPrefix.empty()) {
                    // Create new non-terminal
                    string newNonTerminal = nonTerminal + "_factored" + to_string(counter++);
                    vector<string> newProductions;

                    // Collect suffixes after removing prefix
                    for (const string& prod : group) {
                        string suffix = trim(prod.substr(currentPrefix.size()));
                        if (suffix.empty()) suffix = "ε";
                        newProductions.push_back(suffix);
                    }

                    newGrammar[newNonTerminal] = newProductions;
                    newGrammar[nonTerminal].push_back(currentPrefix + newNonTerminal);
                    factored = true;
                } else {
                    // No common prefix, add as-is
                    newGrammar[nonTerminal].insert(newGrammar[nonTerminal].end(), group.begin(), group.end());
                }
            } else {
                newGrammar[nonTerminal].push_back(group[0]);
            }
        }

        if (!factored && newGrammar[nonTerminal].empty()) {
            newGrammar[nonTerminal] = productions; // fallback
        }
    }

    grammar = newGrammar; // update original grammar with factored one
}

int main() {
    map<string, vector<string>> grammar;

    readCFG("input_Left Factoring.txt", grammar);
    leftFactor(grammar);
    writeCFG("fine_tuned_Left Factor.txt", grammar);

    cout << "Left factoring applied. Output saved to left_factored_output.txt" << endl;

    return 0;
}
