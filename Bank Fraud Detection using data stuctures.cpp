#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ACCOUNTS = 200;  // Valid account numbers: 0 to 199

struct Transaction {
    int from;
    int to;
    int amount;
    Transaction* next;
};

struct BlacklistNode {
    int account;
    BlacklistNode* next;
};

struct GraphNode {
    int to;
    int amount;
    GraphNode* next;
};

struct PQNode {
    int from;
    int to;
    int amount;
    PQNode* next;
};

class FraudDetectionSystem {
private:
    GraphNode* graph[MAX_ACCOUNTS];
    bool visited[MAX_ACCOUNTS];
    Transaction* transactionLog;
    BlacklistNode* blacklist;
    PQNode* priorityQueue;

public:
    FraudDetectionSystem() {
        for (int i = 0; i < MAX_ACCOUNTS; i++) {
            graph[i] = nullptr;
            visited[i] = false;
        }
        transactionLog = nullptr;
        blacklist = nullptr;
        priorityQueue = nullptr;
    }

    void addTransaction(int from, int to, int amount) {
        if (from < 0 || from >= MAX_ACCOUNTS || to < 0 || to >= MAX_ACCOUNTS) {
            cout << "Error: Invalid account number. Please enter valid accounts (0 - " << MAX_ACCOUNTS - 1 << ").\n";
            return;
        }
        if (amount < 0 || amount > 99999) {
            cout << "Error: Amount must be between 0 and 99999.\n";
            return;
        }

        GraphNode* node = new GraphNode{to, amount, graph[from]};
        graph[from] = node;

        logTransaction(from, to, amount);

        if (amount > 10000)
            insertPriorityQueue(from, to, amount);
    }

    void logTransaction(int from, int to, int amount) {
        Transaction* t = new Transaction{from, to, amount, transactionLog};
        transactionLog = t;
    }

    void addToBlacklist(int account) {
        BlacklistNode* node = new BlacklistNode{account, blacklist};
        blacklist = node;

        ofstream out("blacklist.txt", ios::app);
        if (out.is_open()) {
            out << "Blacklisted Account: " << account << "\n";
            out.close();
        }
    }

    void insertPriorityQueue(int from, int to, int amount) {
        PQNode* node = new PQNode{from, to, amount, nullptr};
        if (!priorityQueue || amount > priorityQueue->amount) {
            node->next = priorityQueue;
            priorityQueue = node;
        } else {
            PQNode* current = priorityQueue;
            while (current->next && current->next->amount > amount) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }

    bool detectCycle(int start) {
        int queue[MAX_ACCOUNTS], front = 0, rear = 0;
        for (int i = 0; i < MAX_ACCOUNTS; i++)
            visited[i] = false;

        queue[rear++] = start;
        visited[start] = true;

        while (front < rear) {
            int current = queue[front++];
            GraphNode* temp = graph[current];
            while (temp) {
                if (!visited[temp->to]) {
                    visited[temp->to] = true;
                    queue[rear++] = temp->to;
                } else if (temp->to == start) {
                    cout << "Alert: Fraud cycle detected involving account " << start << ".\n";
                    ofstream out("fraud_log.txt", ios::app);
                    if (out.is_open()) {
                        out << "Fraud cycle detected from account: " << start << "\n";
                        out.close();
                    }
                    addToBlacklist(start);
                    return true;
                }
                temp = temp->next;
            }
        }
        return false;
    }

    void printTransactionLog() {
        cout << "\nTransaction Log:\n";
        Transaction* t = transactionLog;
        while (t) {
            cout << "From: " << t->from << "   To: " << t->to << "   Amount: " << t->amount << "\n";
            t = t->next;
        }
    }

    void printHighValueTransactions() {
        cout << "\nHigh-Value Transactions:\n";
        PQNode* p = priorityQueue;
        while (p) {
            cout << "From: " << p->from << "   To: " << p->to << "   Amount: " << p->amount << "\n";
            p = p->next;
        }
    }

    void printBlacklist() {
        cout << "\nBlacklisted Accounts:\n";
        BlacklistNode* b = blacklist;
        while (b) {
            cout << "Account: " << b->account << "\n";
            b = b->next;
        }
    }

    void loadFromFile(const char* filename) {
        ifstream in(filename);
        if (!in.is_open()) {
            cout << "Error: Could not open file: " << filename << "\n";
            return;
        }

        int from, to, amount;
        while (in >> from >> to >> amount) {
            addTransaction(from, to, amount);
            detectCycle(from);
        }

        in.close();
        cout << "Transactions successfully loaded from file: " << filename << "\n";
    }

    void exportHighValueTransactions() {
        ofstream out("high_value_transactions.txt");
        PQNode* p = priorityQueue;
        while (p && out.is_open()) {
            out << "From: " << p->from << "   To: " << p->to << "   Amount: " << p->amount << "\n";
            p = p->next;
        }
        out.close();
        cout << "High-value transactions exported to high_value_transactions.txt\n";
    }

    void exportBlacklist() {
        ofstream out("blacklisted_accounts.txt");
        BlacklistNode* b = blacklist;
        while (b && out.is_open()) {
            out << "Account: " << b->account << "\n";
            b = b->next;
        }
        out.close();
        cout << "Blacklisted accounts exported to blacklisted_accounts.txt\n";
    }

    void exportTransactionLog() {
        ofstream out("transaction_log.txt");
        Transaction* t = transactionLog;
        while (t && out.is_open()) {
            out << "From: " << t->from << "   To: " << t->to << "   Amount: " << t->amount << "\n";
            t = t->next;
        }
        out.close();
        cout << "Transaction log exported to transaction_log.txt\n";
    }

    void runInterface() {
        cout << "\n*******************************************************\n";
        cout << "*             Banking Fraud Detection System          *\n";
        cout << "*   Project for detecting fraudulent banking activity *\n";
        cout << "*       using graphs, queues, and linked lists        *\n";
        cout << "*******************************************************\n";

        int choice;
        while (true) {
            cout << "\n===== Banking Fraud Detection Menu =====\n";
            cout << "1. Make a Transaction\n";
            cout << "2. Show Transaction Log\n";
            cout << "3. Show High-Value Transactions\n";
            cout << "4. Show Blacklisted Accounts\n";
            cout << "5. Load Transactions from File\n";
            cout << "6. Export High-Value Transactions to File\n";
            cout << "7. Export Blacklist to File\n";
            cout << "8. Export Transaction Log to File\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                int from, to, amount;
                cout << "Enter sender account (0 - " << MAX_ACCOUNTS - 1 << "): ";
                cin >> from;
                cout << "Enter receiver account (0 - " << MAX_ACCOUNTS - 1 << "): ";
                cin >> to;
                cout << "Enter amount: ";
                cin >> amount;
                addTransaction(from, to, amount);
                detectCycle(from);
            } else if (choice == 2) {
                printTransactionLog();
            } else if (choice == 3) {
                printHighValueTransactions();
            } else if (choice == 4) {
                printBlacklist();
            } else if (choice == 5) {
                char filename[100];
                cout << "Enter filename (e.g., transactions.txt): ";
                cin >> filename;
                loadFromFile(filename);
            } else if (choice == 6) {
                exportHighValueTransactions();
            } else if (choice == 7) {
                exportBlacklist();
            } else if (choice == 8) {
                exportTransactionLog();
            } else if (choice == 9) {
                cout << "\nThank you for using the Banking Fraud Detection System. Stay safe!\n";
                break;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    FraudDetectionSystem system;
    system.runInterface();
    return 0;
}

