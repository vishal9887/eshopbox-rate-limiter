# Rate Limiter

A simple rate limiter that allows max N requests per second.

## Run

```
node test.js
```

## How it works

I'm tracking the current second and keeping a counter. When a new second starts, counter resets to 0. If counter is under the limit, allow the request, otherwise reject.

## Thread safety

I used JavaScript because Node.js is single threaded. The event loop processes one thing at a time so `allowRequest()` can never run twice at the same moment. No locks needed, no race conditions possible.
