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
    FileGuard f(file.c_str());
    std::string line;
    getline(f.getStream(), line);
    if(line.compare(DATABASEFORMAT)) throw std::logic_error("Error: database format");
    while (getline(f.getStream(), line)) { insertFromString(line); }
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
        throw std::logic_error("Error: database format");
    }
    if(!isValidDate(year, month, day)){
        std::stringstream ss;
        ss << "Error: year, month or day out of range." << year << "-" << month << "-" << day;
        throw std::out_of_range(ss.str());
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

    ///後で設計

    throw std::runtime_error("Insufficient data. Please add more data.");
    return 0;
}

void  BitcoinExchange::addData(int year, int month, int day, double value) {
    if(!isValidDate(year, month,day)) {
        std::stringstream ss;
        ss << "Error: year, month or day out of range." << year << "-" << month << "-" << day;
        throw std::out_of_range(ss.str());
    }
    data_[year][month][day] = value;
}

void    BitcoinExchange::findOrFail(int year, int month, int day) {
    BitCoinMap::iterator yearIt = data_.find(year);
    if (yearIt != data_.end()) {
        MonthMap::iterator monthIt = yearIt->second.find(month);
        if (monthIt != yearIt->second.end()) {
            DayMap::iterator dayIt = monthIt->second.find(day);
            if (dayIt != monthIt->second.end()) {
                std::cout << \
                year << "-" << \
                std::setw(2) << std::setfill('0') << month << "-" << \
                std::setw(2) << std::setfill('0') << day << \
                " = [ "  << \
                getBitcoinExchangeRate(year, month, day) << " ]" << std::endl;
                return;
            }
        }
    }
    std::stringstream ss;
    ss << year << '-'
       << std::setw(2) << std::setfill('0') << month << '-'
       << std::setw(2) << std::setfill('0') << day;
    std::string message = ss.str();

    //後で帰る
    
    throw FindOrFailException(message.c_str());
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
