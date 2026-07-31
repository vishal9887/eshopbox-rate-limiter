#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <ctime>
using namespace std;

int maxReq = 10;
time_t windowStart = time(NULL);
int count = 0;
mutex mtx;
atomic<int> allowed(0);

bool allowRequest() {
    lock_guard<mutex> lock(mtx);
    time_t now = time(NULL);
    if (now != windowStart) {
        windowStart = now;
        count = 0;
    }
    if (count < maxReq) {
        count++;
        return true;
    }
    return false;
}

void worker() {
    for (int i = 0; i < 100; i++)
        if (allowRequest()) allowed++;
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < 50; i++)
        threads.push_back(thread(worker));
    for (auto& t : threads)
        t.join();

    cout << "Allowed: " << allowed << " (limit=" << maxReq << ")" << endl;
    cout << (allowed <= maxReq ? "PASS" : "FAIL") << endl;
}
