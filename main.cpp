#include <iostream>
#include <syncstream>
#include <chrono>
#include <future>
#include <thread>

using namespace std;

void quick(const std::string& name){
    this_thread::sleep_for(chrono::seconds(1));
    osyncstream(cout) << name << endl;
}

void slow(const std::string& name){
    this_thread::sleep_for(chrono::seconds(7));
    osyncstream(cout) << name << endl;
}

void work(){
    auto start = chrono::high_resolution_clock::now();

    future<void> A1 = async(launch::async, slow, "A1"); 
    future<void> A2 = async(launch::async, quick, "A2"); 

    A2.wait(); 
    future<void> B2 = async(launch::async, quick, "B2"); 
    future<void> C2 = async(launch::async, quick, "C2"); 

    A1.wait(); 
    future<void> B1 = async(launch::async, slow, "B1"); 
    future<void> C1 = async(launch::async, quick, "C1"); 

    B1.wait();
    future<void> D = async(launch::async, quick, "D");

    D.wait();     
    C1.wait();    
    C2.wait();    

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time: " << elapsed.count() << " s\n";


}

int main(){
    work();
    cout << "Work is done!" <<endl;
    return 0;
}