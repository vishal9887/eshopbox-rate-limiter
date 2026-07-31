# Rate Limiter

Limits API calls to max N per second.

## Run

```
node test.js
```

## How it works

I keep track of the current second and a counter. Every time `allowRequest()` is called I check — are we still in the same second? If yes and counter is under the limit, allow it. If counter hit the limit, reject it. When a new second starts, counter resets.

## Thread safety

Node.js is single threaded so only one call runs at a time. No two calls to `allowRequest()` can happen at the same moment. So no locks or mutex needed — it's safe by default.

## Test

The test fires 5000 requests with a limit of 10. Only 10 get through. Rest are rejected.
