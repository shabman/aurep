#ifndef AUREP_UTILS_H
#define AUREP_UTILS_H

#include <cmath>
#include <sstream>

namespace aurep::utils
{
__attribute__((unused)) static void
fprecision(const size_t padding, float& value)
{
    float n = std::pow(10.0f, padding);
    value   = std::round(value * n) / n;
}

__attribute__((unused)) static float
f2dp(const float value)
{
    return std::round(value * 100.0f) / 100.0f;
}

static float
formatTimeFloat(double totalSecs)
{
    int minutes = static_cast<int>(totalSecs / 60);
    int seconds = static_cast<int>(std::fmod(totalSecs, 60));

    std::ostringstream oss;
    oss << minutes << "." << std::setw(2) << std::setfill('0') << seconds;

    return std::stof(oss.str());
}
} // namespace aurep::utils

#endif /* AUREP_UTILS_H */