#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cstring>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <vector>

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[m"

class PmergeMe {
	typedef std::list<int>::iterator IntListIterator;

	typedef std::vector<int>::iterator IntVecIterator;

	typedef enum {
		LIST,
		VECTOR,
	} E_Type;

private:
	std::list<int> input_;
	std::list<int> List_mainChain_;
	std::vector<int> Vector_mainChain_;
	std::set<int> sorted_;
	int size_;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& r);
	~PmergeMe();
	PmergeMe& operator=(const PmergeMe& other);

	void printClock(std::clock_t start, std::clock_t end, E_Type type) const;
	void isSorted();

	template<typename T>
	void FordJohnsonAlgorithm(int size, T numbers) {
		this->size_ = size;
		try {
			this->initContainer(size, numbers);
		} catch (std::exception& e) {
			std::cerr << e.what() << " "
					  << "line: " << __LINE__ << std::endl;
			exit(1);
		}

		std::clock_t list_start;
		std::clock_t list_end;
		try {
			list_start = std::clock();
			mergeInsertionSort(this->List_mainChain_, 1);
			list_end = std::clock();
		} catch (std::exception& e) {
			std::cerr << e.what() << " "
					  << "line: " << __LINE__ << std::endl;
			exit(1);
		}

		std::clock_t vector_start;
		std::clock_t vector_end;
		try {
			vector_start = std::clock();
			mergeInsertionSort(this->Vector_mainChain_, 1);
			vector_end = std::clock();
		} catch (std::exception& e) {
			std::cerr << e.what() << " "
					  << "line: " << __LINE__ << std::endl;
			exit(1);
		}

		try {
			isSorted();

			std::cout << "Before:  ";
			PmergeMe::printContainer(input_);
			std::cout << "After:   ";
			PmergeMe::printContainer(List_mainChain_);
			printClock(list_start, list_end, LIST);
			printClock(vector_start, vector_end, VECTOR);

		} catch (std::exception& e) {
			std::cerr << e.what() << " "
					  << "line: " << __LINE__ << std::endl;
			exit(1);
		}
	}

private:
	static int stoi(const std::string& str);
	void initContainer(int size, int numbers[]);
	void initContainer(int size, char* numbers);
	void initContainer(int size, char** numbers);
	void initContainer(int size, std::string& numbers);
	void initContainer(int size, const std::string numbers[]);
	static size_t calculateJacobsthalNumber(size_t n);

	/**
	 * list
	 */
	// processPairs
	static bool shouldSwapPairs(const int l, const int r);
	static void swapPairs(std::list<int>& lst,
		std::list<int>::iterator leftStart,
		std::list<int>::iterator leftEnd,
		std::list<int>::iterator rightStart,
		std::list<int>::iterator rightEnd);
	static void processPairs(std::list<int>& lst, std::list<int>& subChain, int pairSize);

	// splitIntoMainAndSubChains
	static void splitIntoMainAndSubChains(std::list<int>& mainChain,
		std::list<int>& subChain,
		int pairSize);

	// first insert
	static void prependFirstOfSubchainToMain(std::list<int>& mainChain,
		std::list<int>& subChain,
		int pairSize);

	// insert
	void mergeSubIntoMain(std::list<int>& mainChain,
		std::list<int>& subChain,
		int pairSize,
		std::list<int>& tmp);
	static int lower_bound(std::list<int>& mainChain, int key, int pairSize, int endpoint);
	static void createComparisonListFromMainChain(std::list<int>& lst,
		std::list<int>& mainChain,
		int pairSize,
		int endpoint);
	static bool elementExceedsKey(const std::list<int>& lst, int index, int key);
	static int find_lower_bound(const std::list<int>& lst, int key);
	static void insertSegmentToMainChain(std::list<int>& mainChain,
		std::list<int>& subChain,
		int segmentStart,
		int segmentEnd,
		int insertionPoint,
		int pairSize);

	/**
	 * vector
	 */
	// processPairs
	static bool shouldSwapPairs(const std::vector<int>& vec, int pairSize, int startIndex);
	static void swapPairs(std::vector<int>& vec,
		std::vector<int>::iterator leftStart,
		std::vector<int>::iterator leftEnd,
		std::vector<int>::iterator rightStart,
		std::vector<int>::iterator rightEnd);
	static bool hasPair(const std::vector<int>& vec, int pairSize, size_t startIndex);
	static void processPairs(std::vector<int>& vec, std::vector<int>& subChain, int pairSize);

	// splitIntoMainAndSubChains
	static void splitIntoMainAndSubChains(std::vector<int>& mainChain,
		std::vector<int>& subChain,
		int pairSize);

	// first insert
	static void prependFirstOfSubchainToMain(std::vector<int>& mainChain,
		std::vector<int>& subChain,
		int pairSize);

	// // insert
	void mergeSubIntoMain(std::vector<int>& mainChain,
		std::vector<int>& subChain,
		int pairSize,
		std::vector<int>& tmp);
	static int lower_bound(std::vector<int>& mainChain, int key, int pairSize, int endpoint);
	static void createComparisonVectorFromMainChain(std::vector<int>& vec,
		std::vector<int>& mainChain,
		int pairSize,
		int endpoint);
	static bool elementExceedsKey(const std::vector<int>& vec, int index, int key);
	static int find_lower_bound(const std::vector<int>& vec, int key);
	static void insertSegmentToMainChain(std::vector<int>& mainChain,
		std::vector<int>& subChain,
		int segmentStart,
		int segmentEnd,
		int insertionPoint,
		int pairSize);

	template<typename T>
	void mergeInsertionSort(T& mainChain, int pairSize) {
		if (mainChain.size() / pairSize < 2)
			return;
		T subChain;
#ifdef PAIR
#ifdef LISTDEBUG
		testPairDebug(mainChain, pairSize, "Before process pairs.");
#endif
#ifdef VECTORDEBUG
		testPairDebug(mainChain, pairSize, "Before process pairs.");
#endif
#endif
		processPairs(mainChain, subChain, pairSize);
#ifdef PAIR
#ifdef LISTDEBUG
		testPairDebug(mainChain, pairSize, "After process pairs.");
#endif
#ifdef VECTORDEBUG
		testPairDebug(mainChain, pairSize, "After process pairs.");
#endif
#endif
		T tmp(subChain);
		subChain.clear();

		mergeInsertionSort(mainChain, pairSize * 2);

#ifdef SEPARATE
#ifdef LISTDEBUG
		testSeparateDebug(mainChain, subChain, pairSize, "Before split into main and sub-chains.");
#endif
#ifdef VECTORDEBUG
		testSeparateDebug(mainChain, subChain, pairSize, "Before split into main and sub-chains.");
#endif
#endif
		splitIntoMainAndSubChains(mainChain, subChain, pairSize);
#ifdef SEPARATE
#ifdef LISTDEBUG
		testSeparateDebug(mainChain, subChain, pairSize, "After split into main and sub-chains.");
#endif
#ifdef VECTORDEBUG
		testSeparateDebug(mainChain, subChain, pairSize, "After split into main and sub-chains.");
#endif
#endif

#ifdef FIRST
#ifdef LISTDEBUG
		testFirstInsertDebug(mainChain, subChain, pairSize, "Before prepend sub-chain to main.");
#endif
#ifdef VECTORDEBUG
		testFirstInsertDebug(mainChain, subChain, pairSize, "Before prepend sub-chain to main.");
#endif
#endif
		prependFirstOfSubchainToMain(mainChain, subChain, pairSize);
#ifdef FIRST
#ifdef LISTDEBUG
		testFirstInsertDebug(mainChain, subChain, pairSize, "After prepend sub-chain to main.");
#endif
#ifdef VECTORDEBUG
		testFirstInsertDebug(mainChain, subChain, pairSize, "After prepend sub-chain to main.");
#endif
#endif

#ifdef INSERT
#ifdef LISTDEBUG
		testInsertDebug(mainChain, subChain, pairSize, "Before merge insert", 0, 0);
#endif
#ifdef VECTORDEBUG
		testInsertDebug(mainChain, subChain, pairSize, "Before merge insert", 0, 0);
#endif
#endif
		mergeSubIntoMain(mainChain, subChain, pairSize, tmp);
#ifdef INSERT
#ifdef LISTDEBUG
		testInsertDebug(mainChain, subChain, pairSize, "After merge Insert", 0, 0);
#endif
#ifdef VECTORDEBUG
		testInsertDebug(mainChain, subChain, pairSize, "After merge Insert", 0, 0);
#endif
		std::cout << std::endl << std::endl;
#endif
	}

	// utils
private:
	template<typename T>
	static typename std::vector<T>::iterator getIteratorAt(std::vector<T>& vec, size_t index) {
		if (index >= vec.size()) {
			return vec.end();
		}

		typename std::vector<T>::iterator it = vec.begin();
		it += index;
		return it;
	}

	template<typename T>
	static typename std::list<T>::iterator getIteratorAt(std::list<T>& lst, size_t index) {
		if (index >= lst.size()) {
			return lst.end();
		}

		typename std::list<T>::iterator it = lst.begin();
		std::advance(it, index);
		return it;
	}

	template<typename T>
	static typename std::vector<T>::const_iterator getConstIteratorAt(const std::vector<T>& vec,
		size_t index) {
		if (index >= vec.size()) {
			return vec.end();
		}

		typename std::vector<T>::const_iterator it = vec.begin();
		it += index;
		return it;
	}

	template<typename T>
	static typename std::list<T>::const_iterator getConstIteratorAt(const std::list<T>& lst,
		size_t index) {
		if (index >= lst.size()) {
			return lst.end();
		}

		typename std::list<T>::const_iterator it = lst.begin();
		std::advance(it, index);
		return it;
	}

	template<typename T>
	static void advanceTo(std::vector<T>& vec,
		typename std::vector<T>::iterator& itr,
		size_t index) {
		if (itr + index < vec.end()) {
			itr += index;
		} else {
			itr = vec.end();
		}
	}

	template<typename T>
	static void advanceTo(std::list<T>& lst, typename std::list<T>::iterator& itr, size_t index) {
		for (size_t i = 0; i < index; ++i) {
			if (itr == lst.end())
				return;
			++itr;
		}
		return;
	}

	template<typename T>
	static T getElementAtIndex(const std::vector<T>& vec, size_t index) {
		if (index >= vec.size()) {
			throw std::out_of_range("Index out of bounds");
		}

		return vec[index];
	}

	template<typename T>
	static T getElementAtIndex(const std::list<T>& lst, size_t index) {
		if (index >= lst.size()) {
			throw std::out_of_range("Index out of bounds");
		}

		typename std::list<T>::const_iterator it = getConstIteratorAt(lst, index);

		return *it;
	}

public:
	template<typename T>
	static void printContainer(const T& container) {
		for (typename T::const_iterator it = container.begin(); it != container.end();) {
			std::cout << *it;
			++it;
			if (it != container.end())
				std::cout << " ";
		}
		std::cout << std::endl;
	}

public:
	template<typename T>
	static void testPairDebug(T main, int pairSize, const std::string& s) {
		typedef typename T::iterator Iter;
		int i = 0;
		if (s.compare(0, 6, "Before", 0, 6) == 0) {
			std::cout << CYAN
					  << "-----------------------------------------------------------"
						 "----------------------------------------------------------"
					  << RESET << std::endl
					  << std::endl;
			std::cout << GREEN;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
		} else {
			std::cout << YELLOW;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
		}
		for (Iter it = main.begin(); it != main.end(); ++it) {
			if (i == 0)
				std::cout << " [ ";
			std::cout << *it;
			++i;
			if (i == pairSize) {
				std::cout << " | ";
			} else {
				std::cout << " ";
			}
			if (i == pairSize * 2) {
				std::cout << "] ";
				i = 0;
			}
		}
		std::cout << std::endl << std::endl;
		;
	}

	template<typename T>
	static void testSeparateDebug(T main, T sub, int pairSize, const std::string& s) {
		typedef typename T::iterator Iter;
		int i = 0;
		if (s.compare(0, 6, "Before", 0, 6) == 0) {
			std::cout << CYAN
					  << "-----------------------------------------------------------"
						 "----------------------------------------------------------"
					  << RESET << std::endl
					  << std::endl;
			std::cout << GREEN;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
			for (Iter it = main.begin(); it != main.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " | ";
				} else {
					std::cout << " ";
				}
				if (i == pairSize * 2) {
					std::cout << "] ";
					i = 0;
				}
			}
			std::cout << std::endl << std::endl;
			;
		} else {
			std::cout << YELLOW;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
			std::cout << BLUE;
			std::cout << "main-chain" << std::endl;
			std::cout << RESET;
			for (Iter it = main.begin(); it != main.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " ] ";
					i = 0;
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
			i = 0;
			std::cout << BLUE;
			std::cout << "sub-chain" << std::endl;
			std::cout << RESET;
			for (Iter it = sub.begin(); it != sub.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " ] ";
					i = 0;
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl << std::endl;
			;
		}
	}

	template<typename T>
	static void testFirstInsertDebug(T main, T sub, int pairSize, const std::string& s) {
		typedef typename T::iterator Iter;
		int i = 0;
		if (s.compare(0, 6, "Before", 0, 6) == 0) {
			std::cout << CYAN
					  << "-----------------------------------------------------------"
						 "----------------------------------------------------------"
					  << RESET << std::endl
					  << std::endl;
			std::cout << GREEN;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
		} else {
			std::cout << YELLOW;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
			std::cout << BLUE;
			std::cout << "main-chain" << std::endl;
			std::cout << RESET;
		}
		for (Iter it = main.begin(); it != main.end(); ++it) {
			if (i == 0)
				std::cout << " [ ";
			std::cout << *it;
			++i;
			if (i == pairSize) {
				std::cout << " ] ";
				i = 0;
			} else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
		i = 0;
		std::cout << BLUE;
		std::cout << "sub-chain" << std::endl;
		std::cout << RESET;
		for (Iter it = sub.begin(); it != sub.end(); ++it) {
			if (i == 0)
				std::cout << " [ ";
			std::cout << *it;
			++i;
			if (i == pairSize) {
				std::cout << " ] ";
				i = 0;
			} else {
				std::cout << " ";
			}
		}
		std::cout << std::endl << std::endl;
		;
	}

	template<typename T>
	static void testInsertDebug(T main,
		T sub,
		int pairSize,
		const std::string& s,
		int key,
		int jacoNum) {
		typedef typename T::iterator Iter;
		int i = 0;
		if (s.compare(0, 6, "Before", 0, 6) == 0) {
			std::cout << CYAN
					  << "-----------------------------------------------------------"
						 "----------------------------------------------------------"
					  << RESET << std::endl
					  << std::endl;
			std::cout << GREEN;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
			for (Iter it = main.begin(); it != main.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " ] ";
					i = 0;
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
			i = 0;
			std::cout << BLUE;
			std::cout << "sub-chain" << std::endl;
			std::cout << RESET;
			for (Iter it = sub.begin(); it != sub.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " ] ";
					i = 0;
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl << std::endl;
			;
		} else if (s.compare(0, 5, "After", 0, 5) == 0) {
			std::cout << YELLOW;
			std::cout << s << " pairSize: " << pairSize << std::endl;
			std::cout << RESET;
			std::cout << BLUE;
			std::cout << "main-chain" << std::endl;
			std::cout << RESET;
			i = 0;
			for (Iter it = main.begin(); it != main.end(); ++it) {
				if (i == 0)
					std::cout << " [ ";
				std::cout << *it;
				++i;
				if (i == pairSize) {
					std::cout << " ] ";
					i = 0;
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
			std::cout << BLUE;
			std::cout << "sub-chain" << std::endl;
			std::cout << RESET;
			for (Iter it = sub.begin(); it != sub.end(); ++it) {
				std::cout << *it;
				std::cout << " ";
			}
			std::cout << std::endl << std::endl;
			;
		} else {
			std::cout << BLUE << "[" << RESET << "n: " << jacoNum << " key: " << key << BLUE << "]"
					  << RESET;
		}
	}
};

#endif
