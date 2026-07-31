const RateLimiter = require("./rateLimiter");

const rl = new RateLimiter(10);
let allowed = 0;

for (let i = 0; i < 5000; i++) {
    if (rl.allowRequest()) allowed++;
}

console.log(`Allowed: ${allowed} (limit=10)`);
console.log(allowed <= 10 ? "PASS" : "FAIL");
