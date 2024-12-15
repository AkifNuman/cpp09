#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::ReadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        float value;
        if (std::getline(ss, date, ',') && (ss >> value))
        {
            database[date] = value; // Tarih ve fiyatı ekle
        }
    }
    file.close();
}

void BitcoinExchange::Evaluate(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, value_str;
        if (std::getline(ss, date, '|') && std::getline(ss, value_str))
        {
            date = date.substr(0, date.find_last_not_of(" \t") + 1);
            value_str = value_str.substr(value_str.find_first_not_of(" \t"));

            if (!isValidDate(date))
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }

            std::istringstream value_stream(value_str);
            float value;
            if (!(value_stream >> value) || value < 0)
            {
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }
            if (value > 1000)
            {
                std::cerr << "Error: too large a number." << std::endl;
                continue;
            }

            std::map<std::string, float>::iterator it = database.lower_bound(date);
            if (it == database.end() || it->first != date)
            {
                if (it != database.begin())
                {
                    --it;
                }
            }

            if (it != database.end())
            {
                float rate = it->second;
                std::cout << date << " => " << value << " = " << value * rate << std::endl;
            }
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    std::istringstream ss(date);
    int year, month, day;
    char dash1, dash2;
    if (ss >> year >> dash1 >> month >> dash2 >> day && dash1 == '-' && dash2 == '-')
    {
        if (year >= 2009 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
        {
            return true;
        }
    }
    return false;
}

bool BitcoinExchange::isValidValue(const std::string &value) const
{`
    std::istringstream ss(value);
    float val;
    if (ss >> val && val >= 0)
    {
        return true;
    }
    return false;
}
