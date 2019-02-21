//
// Created by octavarrium on 19-2-21.
//
#pragma once

#include <cstdint>
#include <string>
#include "copyable.hpp"

class Timestamp : copyable {
public:
    Timestamp();

    explicit Timestamp(int64_t microSecondSinceEpoch);

    void swap(Timestamp& that) {
        std::swap(_microSecondSinceEpoch, that._microSecondSinceEpoch);
    }
    std::string toString() const;

    std::string toFormattedString() const;

    bool isValid() const { return _microSecondSinceEpoch > 0; };

    int64_t getMicroSecondSinceEpoch() const { return _microSecondSinceEpoch; }

    static Timestamp now();

    static Timestamp invalid();
    static const int microSecondsPerSecond = 1000 * 1000;
private:
    int64_t _microSecondSinceEpoch;
};


inline bool operator<(Timestamp lhs, Timestamp rhs)
{
    return lhs.getMicroSecondSinceEpoch() < rhs.getMicroSecondSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
    return lhs.getMicroSecondSinceEpoch() == rhs.getMicroSecondSinceEpoch();
}

inline double timeDifference(Timestamp high, Timestamp low)
{
    int64_t diff = high.getMicroSecondSinceEpoch() - low.getMicroSecondSinceEpoch();
    return static_cast<double>(diff) / Timestamp::microSecondsPerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds)
{
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::microSecondsPerSecond);
    return Timestamp(timestamp.getMicroSecondSinceEpoch() + delta);
}