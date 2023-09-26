#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};

PmergeMe::PmergeMe(const PmergeMe & r): v_mainChain_(r.v_mainChain_), l_mainChain_(r.l_mainChain_) {};

PmergeMe::~PmergeMe() {};

PmergeMe & PmergeMe::operator= (const PmergeMe &other) {
    if( this != &other ) {
        this->v_mainChain_ = other.v_mainChain_;
        this->l_mainChain_ = other.l_mainChain_;
    }
    return *this;
}

typedef std::vector<int>::const_iterator cv_itr;
typedef std::vector<int>::iterator v_itr;
typedef std::vector<v_itr>::iterator vi_itr;

typedef std::list<int>::const_iterator cl_itr;
typedef std::list<int>::iterator l_itr;

/**
 * pair comparison
*/
int     PmergeMe::comparison(int pairSize, std::vector<int> & v, int start) {
    if(v.size() <= static_cast<size_t>(pairSize + start))
        return -1;
    if(v[start] < v[pairSize+ start])
        return 1;
    return 0;
}

void    PmergeMe::swap(int pairSize, std::vector<int> & v, int start) {
    for(int i=0; i < pairSize; ++i) {
        std::iter_swap(v.begin() + start, v.begin() + start + pairSize);
        ++start;
    }
}

int PmergeMe::checkOverflow(int pairSize, std::vector<int> & v, int start) {
    size_t size = v.size() - 1;

    for(int i=0; i < pairSize; ++i) {
        if(static_cast<size_t>(start + pairSize) > size)
            return true;
        ++start;
    }
    return false;
}

void    PmergeMe::pairwiseComparison(int pairSize, std::vector<int> & v, std::vector<int> & subChain) {
    for ( std::size_t i=0; i < v.size();) {
        if(checkOverflow(pairSize,v,i))
        {
            subChain.insert(subChain.begin(), v.begin() + i,v.end() );
            v.erase(v.begin() + i, v.end());
            for ( ; ; ) {
                if(subChain.size() == static_cast<std::size_t>(pairSize))
                    break;
                subChain.push_back(-1);
            }
            break;
        }
        if(comparison(pairSize,v,i)) {
                swap(pairSize,v,i);
        }
        i+=pairSize;
        i+=pairSize;
    }
}

/**
 * separate mainChain SubChain
*/
void PmergeMe::separateMainChainAndSubChain(std::vector<int> & v, std::vector<int> & subChain, int pairSize) {
    int end = v.size();

    int over;
    int size = subChain.size();
    for ( int i=0; i < end;) {
        if(checkOverflow(pairSize,v,i))
        {
            over = i;
            for(int k=i; k<end;++k) {
                subChain.insert(subChain.end() - size, v[k]);
            }
            break;
        }
        i+=pairSize;
        for (int k=0; k<pairSize; ++k) {
            subChain.insert(subChain.end() - size, v[i + k]);
        }
        i+=pairSize;
    }
    
    int ep=0;
    v_itr it=v.begin(); 
    for ( ;it != v.end(); ++it) {
        if(ep == over)
            break;
        ep++;
    }

    int beginPostion = pairSize;
    for ( ;; ) {
        v.erase(v.begin() + beginPostion, v.begin() + beginPostion + pairSize);
        if(v.begin() + beginPostion == v.end()) { break; }
        beginPostion += pairSize;
    }
}

/**
 * insert first subPair
*/

void PmergeMe::insertAtTheStart(std::vector<int> & mainChain, std::vector<int> & subChain, int pairSize) {
    mainChain.insert(mainChain.begin(), subChain.begin(), subChain.begin() + pairSize);
}

/**
 * insert
*/
bool PmergeMe::isKey(std::vector<v_itr> iterators, int index, int key) {
    if (*(iterators[index]) >= key) return true;
    else return false;
}

v_itr PmergeMe::lower_bound(std::vector<v_itr>& iterators, vi_itr begin, vi_itr end, int key, int right) {
    int left = -1;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;

        if (isKey(iterators, mid, key)) right = mid;
        else left = mid;
    }

    return *(iterators.begin() + right);
}

//構造体作るしかなさそう
v_itr   PmergeMe::binarySearch(std::vector<int> & v, int key, int pairSize, int keyPosition) {
    std::vector<v_itr> iterators;

    for (v_itr itr = v.begin(); itr != v.end(); itr += pairSize) {
        iterators.push_back(itr);
    }
    return lower_bound(iterators, iterators.begin(), iterators.end(), key, iterators.size());
}

int PmergeMe::jacobsthalNumber(int n) {

    if (n <= 0) return 0;
    if (n == 1) return 1;

    return jacobsthalNumber(n - 1) + (2 * (jacobsthalNumber(n - 2)));
}

void PmergeMe::insertionFromSubIntoMain(std::vector<int> & mainChain, std::vector<int> & subChain, int pairSize) {
    
    #ifdef SORT
        std::cout << "==================================================================================================================================================================================================================================" <<pairSize << std::endl;
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "sort");
    #endif
    int prev;
    int now;
    int n = 3;
    int insertSize = pairSize;
    for ( ;; ) {
       
        prev = jacobsthalNumber(n-1);
        if(prev > ( subChain.size()/pairSize) )
            break;
        now = jacobsthalNumber(n);
        if( insertSize >= subChain.size() ) break;
        if(now > (subChain.size()/pairSize) ) {
            now = (subChain.size()/pairSize) - 1;

            v_itr it = binarySearch(mainChain, *(subChain.begin()+ (now * pairSize)), pairSize, 0);
            mainChain.insert(it, (subChain.begin()+ (now * pairSize)) , subChain.end());
            insertSize += std::distance(subChain.begin() + (now * pairSize) , subChain.end());
            --now;
            --prev;
        } else {
            --now;
            --prev;
        }
        for( ;; ) {
            if( (now == prev) || (now < 0) || (insertSize >= subChain.size()) ) break;
            v_itr it = binarySearch(mainChain, *(subChain.begin()+ (now * pairSize)), pairSize, 0);
            mainChain.insert(it, (subChain.begin()+ (now * pairSize)) , (subChain.begin()+ (now * pairSize) + pairSize));
            insertSize += pairSize;
            --now;
        }
        ++n;
    }
    
    subChain.clear();
    #ifdef SORT
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "sort");
    #endif
}

void PmergeMe::mergeInsertionSort(std::vector<int> & mainChain,int pairSize) {
    if( (mainChain.size() / pairSize)  <= 2 ) { 
        #ifdef PAIR
            this->printDebug<std::vector<int> >(mainChain, std::vector<int>(), pairSize, "pair");
        #endif    
        return ; 
    } 
    
    std::vector<int> subChain;
    #ifdef PAIR
        this->printDebug<std::vector<int> >( mainChain, subChain, pairSize, "Before pair");
    #endif
    pairwiseComparison(pairSize, mainChain, subChain);
    #ifdef PAIR
        this->printDebug<std::vector<int> >( mainChain, subChain, pairSize, "After pair");
    #endif
    
    mergeInsertionSort(mainChain, pairSize * 2);

    #ifdef SEPARATE
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "Before separating.");
    #endif
    separateMainChainAndSubChain(mainChain, subChain, pairSize);
    #ifdef SEPARATE
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "After separating.");
    #endif

    #ifdef INSERTATTHESTART
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "Before Insert the first value.");
    #endif
    insertAtTheStart(mainChain, subChain, pairSize);
    #ifdef INSERTATTHESTART
        this->printDebug<std::vector<int> >(mainChain, subChain, pairSize, "After Insert the first value.");
    #endif

    insertionFromSubIntoMain(mainChain, subChain, pairSize);
}


void    PmergeMe::initContainer(int size, int numbers[]) {
    for (int i = 0; i < size; ++i) {
        v_mainChain_.push_back(numbers[i]);     
        l_mainChain_.push_back(numbers[i]);     
    }
}

void PmergeMe::FordJohnsonAlgorithm(int size, int numbers[]) {
    this->initContainer(size, numbers);
    mergeInsertionSort(this->v_mainChain_, 1);

    PmergeMe::print<std::vector<int>, v_itr>(this->v_mainChain_);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q Pmerge");
}