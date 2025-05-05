#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

class Table {
public:
    std::vector<std::string> columns;
    std::vector<std::map<std::string, std::string>> rows;

    Table(const std::vector<std::string>& cols) : columns(cols) {}

    void insert(const std::map<std::string, std::string>& row) {
        rows.push_back(row);
    }

    void select(const std::string& column, const std::string& whereColumn = "", const std::string& whereValue = "") {
        if (std::find(columns.begin(), columns.end(), column) == columns.end()) {
            std::cout << "Column '" << column << "' not found.\n";
            return;
        }

        for (const auto& row : rows) {
            if (whereColumn.empty() || row.at(whereColumn) == whereValue) {
                std::cout << row.at(column) << "\n";
            }
        }
    }

    void update(const std::string& targetColumn, const std::string& newValue,
                const std::string& whereColumn, const std::string& whereValue) {
        for (auto& row : rows) {
            if (row[whereColumn] == whereValue) {
                row[targetColumn] = newValue;
            }
        }
    }

    void remove(const std::string& whereColumn, const std::string& whereValue) {
        rows.erase(std::remove_if(rows.begin(), rows.end(),
            [&](const std::map<std::string, std::string>& row) {
                return row.at(whereColumn) == whereValue;
            }), rows.end());
    }

    void printAll() {
        for (const auto& col : columns) {
            std::cout << col << "\t";
        }
        std::cout << "\n-----------------------------\n";

        for (const auto& row : rows) {
            for (const auto& col : columns) {
                std::cout << row.at(col) << "\t";
            }
            std::cout << "\n";
        }
    }
};

class MiniDatabase {
private:
    std::map<std::string, Table> tables;

public:
    void createTable(const std::string& name, const std::vector<std::string>& columns) {
        tables[name] = Table(columns);
    }

    void insertInto(const std::string& tableName, const std::map<std::string, std::string>& row) {
        tables[tableName].insert(row);
    }

    void query(const std::string& sql) {
        std::istringstream iss(sql);
        std::string command;
        iss >> command;

        if (command == "SELECT") {
            std::string column, from, tableName, where, whereColumn, op, whereValue;
            iss >> column >> from >> tableName;
            if (iss >> where >> whereColumn >> op >> whereValue) {
                whereValue = stripQuotes(whereValue);
                tables[tableName].select(column, whereColumn, whereValue);
            } else {
                tables[tableName].select(column);
            }
        } else if (command == "UPDATE") {
            std::string tableName, set, columnToSet, eq1, newValue, where, whereColumn, eq2, whereValue;
            iss >> tableName >> set >> columnToSet >> eq1 >> newValue >> where >> whereColumn >> eq2 >> whereValue;

            newValue = stripQuotes(newValue);
            whereValue = stripQuotes(whereValue);

            tables[tableName].update(columnToSet, newValue, whereColumn, whereValue);
        } else if (command == "DELETE") {
            std::string from, tableName, where, whereColumn, eq, whereValue;
            iss >> from >> tableName >> where >> whereColumn >> eq >> whereValue;
            whereValue = stripQuotes(whereValue);
            tables[tableName].remove(whereColumn, whereValue);
        } else {
            std::cout << "Unsupported command.\n";
        }
    }

    std::string stripQuotes(const std::string& s) {
        if (s.front() == '\'' && s.back() == '\'') {
            return s.substr(1, s.size() - 2);
        }
        return s;
    }

    void showTable(const std::string& tableName) {
        if (tables.find(tableName) != tables.end()) {
            std::cout << "\n-- Table: " << tableName << " --\n";
            tables[tableName].printAll();
        } else {
            std::cout << "Table not found.\n";
        }
    }
};

int main() {
    MiniDatabase db;

    // Create tables
    db.createTable("ingredients", {"id", "name", "quantity", "unit"});
    db.insertInto("ingredients", {{"id", "1"}, {"name", "Tomato"}, {"quantity", "100"}, {"unit", "kg"}});
    db.insertInto("ingredients", {{"id", "2"}, {"name", "Cheese"}, {"quantity", "20"}, {"unit", "kg"}});
    db.insertInto("ingredients", {{"id", "3"}, {"name", "Bread"}, {"quantity", "50"}, {"unit", "loaves"}});

    // Display initial
    db.showTable("ingredients");

    std::cout << "\n-- UPDATE quantity of Bread --\n";
    db.query("UPDATE ingredients SET quantity = '45' WHERE name == 'Bread'");
    db.showTable("ingredients");

    std::cout << "\n-- DELETE Tomato from ingredients --\n";
    db.query("DELETE FROM ingredients WHERE name == 'Tomato'");
    db.showTable("ingredients");

    return 0;
}
