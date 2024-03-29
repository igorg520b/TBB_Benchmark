#include <iostream>
#include <iomanip>
#include <omp.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <random>
#include <limits>
#include <chrono>
#include <thread>

#include <tbb/concurrent_set.h>
#include <tbb/concurrent_unordered_set.h>



int main()
{
    std::cout << "start" << std::endl;

    std::cout << "num_threads " << omp_get_max_threads() << std::endl;
    std::cout << "testing threads" << std::endl;
#pragma omp parallel
    { std::cout << "  " << omp_get_thread_num() << "  "; }
    std::cout << std::endl;



    typedef unsigned int mytype;
    std::set<mytype> std_set;
    std::unordered_set<mytype> std_unordered_set;
    tbb::concurrent_set<mytype> tbb_set;
    tbb::concurrent_set<mytype> tbb_set2;
    tbb::concurrent_unordered_set<mytype> tbb_unordered_set;

    const unsigned nTests = 4;
    const unsigned nKeys_test_options[nTests] = {1000, 10000, 100000, 1000000};
    const unsigned nValuesInserted = 10000000;
    mytype *random_sequence = new mytype[nValuesInserted];

    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937
    std::uniform_int_distribution<mytype> distr;
    std::cout << "inserting " << nValuesInserted << " elements with N distinct values; time in milliseconds\n";

    std::cout << "\n\n"<< std::left << std::setw(10) << "N" << std::setw(15) << "std_set";
    std::cout << std::setw(15) << "tbb_single" << std::setw(15) << "tbb_multi";
    std::cout << std::setw(15) << "std_unordered" << std::setw(15) << "tbb_unordered" << '\n';


    for(unsigned test=0;test<nTests;test++)
    {
        std_set.clear();
        tbb_set.clear();
        tbb_set2.clear();
        std_unordered_set.clear();
        tbb_unordered_set.clear();

        const unsigned nKeys = nKeys_test_options[test];
        for(unsigned i=0;i<nValuesInserted;i++) random_sequence[i]=distr(eng)%nKeys;

        std::cout << std::left << std::setw(10) << nKeys << std::flush;

        auto t1 = std::chrono::high_resolution_clock::now();
        for(unsigned i=0;i<nValuesInserted;i++) std_set.insert(random_sequence[i]);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto d1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::setw(15) << d1 << std::flush;

        t1 = std::chrono::high_resolution_clock::now();
        for(unsigned i=0;i<nValuesInserted;i++) tbb_set.insert(random_sequence[i]);
        t2 = std::chrono::high_resolution_clock::now();
        auto d2 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::setw(15) << d2 << std::flush;


        t1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
        for(int i=0;i<nValuesInserted;i++) tbb_set2.insert(random_sequence[i]);
        t2 = std::chrono::high_resolution_clock::now();
        auto d3 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::setw(15) << d3 << std::flush;

        t1 = std::chrono::high_resolution_clock::now();
        for(unsigned i=0;i<nValuesInserted;i++) std_unordered_set.insert(random_sequence[i]);
        t2 = std::chrono::high_resolution_clock::now();
        auto d4 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::setw(15) << d4 << std::flush;

        t1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
        for(int i=0;i<nValuesInserted;i++) tbb_unordered_set.insert(random_sequence[i]);
        t2 = std::chrono::high_resolution_clock::now();
        auto d5 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::setw(15) << d5 << std::endl;
    }

    return 0;
}
