#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange exchange;
    exchange.ReadDatabase("data.csv");
    exchange.Evaluate(argv[1]);

    return 0;
}