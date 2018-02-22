#pragma once

namespace emp {

class EntropyQCalc {
#if !NDEBUG
    const unsigned k_;
#endif
    union __union {
        uint8_t counts_[4];
        uint32_t      val_;
        __union(unsigned val): val_(val) {}
    };
    __union u_;
    const double div_;
    EntropyQCalc(unsigned k): k_{k}, u_(0), div_(1./k) {}
    void reset() {u_.val_ = 0;}
    double report() const {
        assert(counts_[0] + counts_[1] + counts_[2] + counts_[3] == k_);
        double t = div_ *counts_[0], sum  = t * std::log2(t);
        t = div_ * counts_[1],       sum += t * std::log2(t);
        t = div_ * counts_[2],       sum += t * std::log2(t);
        t = div_ * counts_[3],       sum += t * std::log2(t);
    }
    template<typename T, typename=std::enable_if_t<std::is_arithmetic_v<T>>>
    void push(T val) {
        assert((val & ~(T(3))) == 0);
    }
};

}
