# Rate Limiter

Limits API calls to max N per second. Uses C++ because the problem needs real multi-threading.

## Compile and Run

```
g++ -std=c++17 -pthread main.cpp -o rate_limiter
./rate_limiter
```

## How it works

I keep track of the current second and a counter. When `allowRequest()` is called, I check if we're still in the same second. If yes and counter is under N, I allow it and increment. If counter hit N, I reject. When a new second starts, counter resets.

## How I made it thread safe

I used `mutex` with `lock_guard`. When a thread enters `allowRequest()`, it locks the mutex. Other threads wait until it's done. This way only one thread can read and update the counter at a time. No two threads can mess with the counter together.

Without this, two threads could both see counter = 9 (limit 10), both think there's room, and both increment — making it 11. The mutex prevents that.

`lock_guard` automatically unlocks when the function returns so you don't have to worry about forgetting to unlock.

## What I was unsure about

I went with a fixed window (reset counter every second) instead of a sliding window. Fixed window is simpler and matches what the problem asks — N calls per second. A sliding window would smooth out bursts better but felt like overkill here.
