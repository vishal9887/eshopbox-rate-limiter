# Rate Limiter

Allows max N API calls per second. Extra calls get rejected.

## Run

```
g++ -std=c++17 -pthread main.cpp -o rate_limiter
./rate_limiter
```

## How it works

I track the current second and a counter. If counter < N, allow the request. If counter hits N, reject. Counter resets every new second.

## Thread safety

I used a `mutex`. It makes sure only one thread can check and update the counter at a time. Without it two threads could both read the counter, both think there's room, and both go through — breaking the limit.

## Unsure about

Fixed window vs sliding window. I went with fixed window since the problem says "N calls per second" and that's exactly what fixed window does.
