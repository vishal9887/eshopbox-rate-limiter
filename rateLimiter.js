class RateLimiter {
    constructor(n) {
        this.maxReq = n;
        this.windowStart = Math.floor(Date.now() / 1000);
        this.count = 0;
    }

    allowRequest() {
        let now = Math.floor(Date.now() / 1000);
        if (now !== this.windowStart) {
            this.windowStart = now;
            this.count = 0;
        }
        if (this.count < this.maxReq) {
            this.count++;
            return true;
        }
        return false;
    }
}

module.exports = RateLimiter;
