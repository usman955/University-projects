#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Reads a CFG from a file and stores it in a map
void loadCFG(const string& filename, map<string, vector<string>>& grammar) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string nonTerminal, arrow, production;
        ss >> nonTerminal >> arrow;

        string remaining;
        getline(ss, remaining);
        stringstream prodStream(remaining);

        vector<string> rules;
        while (getline(prodStream, production, '|')) {
            production.erase(0, production.find_first_not_of(" \t\r\n"));
            production.erase(production.find_last_not_of(" \t\r\n") + 1);
            rules.push_back(production);
        }

        grammar[nonTerminal] = rules;
    }

    infile.close();
}

// Writes a CFG to a file from a map
void saveCFG(const string& filename, const map<string, vector<string>>& grammar) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Cannot write to file " << filename << endl;
        exit(1);
    }

    for (const auto& [nonTerminal, rules] : grammar) {
        outfile << nonTerminal << " -> ";
        for (size_t i = 0; i < rules.size(); ++i) {
            outfile << rules[i];
            if (i < rules.size() - 1) {
                outfile << " | ";
            }
        }
        outfile << endl;
    }

    outfile.close();
}


void fineTuneGrammar(map<string, vector<string>>& grammar) {
    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        string nonTerminal = it->first;
        vector<string> rules = it->second;

        // Separate recursive and non-recursive rules
        vector<string> recursiveRules;
        vector<string> nonRecursiveRules;

        for (const string& rule : rules) {
            if (rule.find(nonTerminal + " ") == 0) { // Check if rule starts with the non-terminal
                recursiveRules.push_back(rule.substr(nonTerminal.size() + 1));
            } else {
                nonRecursiveRules.push_back(rule);
            }
        }

        if (!recursiveRules.empty()) {
            // Create new non-terminal
            string newNonTerminal = nonTerminal + "'";

            // Update the original non-terminal's rules
            grammar[nonTerminal].clear();
            for (const string& rule : nonRecursiveRules) {
                grammar[nonTerminal].push_back(rule + " " + newNonTerminal);
            }

            // Add rules for the new non-terminal
            vector<string> newRules;
            for (const string& rule : recursiveRules) {
                newRules.push_back(rule + " " + newNonTerminal);
            }
            newRules.push_back(""); // Epsilon (ε) production

            grammar[newNonTerminal] = newRules;
        }
    }
}


int main() {
    map<string, vector<string>> grammar;

    // Load CFG from file
    loadCFG("input_left_recursion_CFG.txt", grammar);

    // Apply fine-tuning if needed
    fineTuneGrammar(grammar);

    // Save modified CFG to file
    saveCFG("fine_tune_left_recursion_cfg.txt", grammar);

    cout << "✅ Processed CFG saved to fine_tune_left_recursion_cfg.txt\n";
    return 0;
}
