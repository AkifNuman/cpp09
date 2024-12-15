#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

class BitcoinExchange
{
public:
    BitcoinExchange();
    ~BitcoinExchange();
    void ReadDatabase(const std::string &filename);
    void Evaluate(const std::string &filename);

private:
    std::map<std::string, float> database;
    bool isValidDate(const std::string &date) const;
    bool isValidValue(const std::string &value) const;
};
