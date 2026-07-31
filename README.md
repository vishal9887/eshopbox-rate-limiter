# Rate Limiter

A simple rate limiter that allows max N requests per second.

## Run

```
node test.js
```

## How it works

I'm using a fixed window approach — I track the current second and keep a counter. When a new second starts, counter resets. If counter < N, allow the request, otherwise reject it.

## Thread safety

JavaScript is single threaded — the event loop runs one thing at a time. So `allowRequest()` can never be called by two things at the exact same moment. There's no race condition possible, no need for locks or mutex.

If this was Java or C++ I'd need a mutex because real threads run in parallel there. But in Node.js that's not how it works — even with async stuff like Promise.all or callbacks, they still execute one at a time on the main thread.

## One thing I thought about

At the boundary of two seconds you could get N requests at the end of second 1 and N more at the start of second 2, so 2N in a short burst. A sliding window would fix that but felt like overkill for what the problem is asking.
