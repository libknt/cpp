#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string file) {
    initDatabase(file);
}

BitcoinExchange::BitcoinExchange(BitCoinMap data) : data_(data) {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &r) : data_(r.data_) {};

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange & BitcoinExchange::operator= (const BitcoinExchange &other) {
    if(this != &other)
        this->data_ = other.data_;
    return *this;
}

void BitcoinExchange::initDatabase(std::string file) {
    std::ifstream f(file.c_str());
    if (!f) throw std::runtime_error("Error: could not open database.");
    std::string line;
    getline(f, line);
    if(line.compare(DATABASEFORMAT)) throw std::runtime_error("Error: database format");
    while (getline(f, line)) { insertFromString(line); }
    f.close();
}

void BitcoinExchange::insertData( int year, int month, int day, double value) {
    data_[year][month][day] = value;
}

void BitcoinExchange::insertFromString(const std::string& input) {
    std::istringstream ss(input);
    int year, month, day;
    double value;
    char dash, comma;

    ss >> year >> dash >> month >> dash >> day >> comma >> value;
    
    if (ss.fail() || dash != '-' || comma != DATABASEDELIMITER || !ss.eof()) {
        throw std::runtime_error("Error: database format");
    }
    if( ! validateYear(year) || ! validateMonth(month) || ! validateDay(day)) {
        std::stringstream ss;
        ss << "Error: year, month or day out of range." << year << "-" << month << "-" << day;
        throw std::runtime_error(ss.str());
    }
    insertData(year, month, day, value);
}

double  BitcoinExchange::getBitcoinExchangeRate(int year, int month, int day) {
    if (data_[year][month].find(day) == data_[year][month].end()) {
        return findDataCloseTo(year, month, day);
    }
    return data_[year][month][day];
}

double  BitcoinExchange::findDataCloseTo(int year, int month, int day) {
    int findYear = year;
    int findMonth = month;
    int findDay = day;

    for (; findYear >= MINYEAR; --findYear) {
        BitCoinMap::iterator yearIt = data_.find(findYear);
        if (yearIt != data_.end()) {
            for (; findMonth >= MINMONTH; --findMonth) {
                MonthMap::iterator monthIt = yearIt->second.find(findMonth);
                if (monthIt != yearIt->second.end()) {
                    for (; findDay >= MINDAY; --findDay) {
                        DayMap::iterator dayIt = monthIt->second.find(findDay);
                        if (dayIt != monthIt->second.end()) {
                            return dayIt->second;
                        }
                    }
                    findDay = MAXDAY;
                }
            }
            findMonth = MAXMONTH;
        }
    }

    throw std::runtime_error("Insufficient data. Please add more data.");
    return 0;
}

void  BitcoinExchange::addData(int year, int month, int day, double value) {
    if( ! validateYear(year) || ! validateMonth(month) || ! validateDay(day)) {
        std::stringstream ss;
        ss << "Error: year, month or day out of range." << year << "-" << month << "-" << day;
        throw std::runtime_error(ss.str());
    }
    data_[year][month][day] = value;
}

void    BitcoinExchange::dumpDatabaseData(int year, int month, int day) {
    BitCoinMap::iterator yearIt = data_.find(year);
    if (yearIt != data_.end()) {
        MonthMap::iterator monthIt = yearIt->second.find(month);
        if (monthIt != yearIt->second.end()) {
            DayMap::iterator dayIt = monthIt->second.find(day);
            if (dayIt != monthIt->second.end()) {
                std::cout << dayIt->second << std::endl;
                return;
            }
        }
    }
    std::cerr << "Error: Data not found for the given date." << std::endl;
}

void BitcoinExchange::printDatabase() {
    for (BitCoinMap::const_iterator yearIt = data_.begin(); yearIt != data_.end(); ++yearIt) {
        int year = yearIt->first;
        std::cout << year << std::endl;
        
        for (MonthMap::const_iterator monthIt = yearIt->second.begin(); monthIt != yearIt->second.end(); ++monthIt) {
            int month = monthIt->first;
            std::cout << "  " << month << std::endl;

            for (DayMap::const_iterator dayIt = monthIt->second.begin(); dayIt != monthIt->second.end(); ++dayIt) {
                int day = dayIt->first;
                double value = dayIt->second;
                std::cout << "    " << day << ": " << value << std::endl;
            }
        }
    }
}