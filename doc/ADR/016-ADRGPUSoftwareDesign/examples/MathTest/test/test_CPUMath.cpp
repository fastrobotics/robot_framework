#include <gtest/gtest.h>

#include <array>
#include <memory>

#include "../IVectorMath.hpp"

extern IVectorMath* createCPUMath();

TEST(CPUMath, ComputesExpectedValueForEveryElement) {
    constexpr int count = 4;
    std::array<float, count> a{1.0f, 1.0f, 1.0f, 1.0f};
    std::array<float, count> b{2.0f, 2.0f, 2.0f, 2.0f};
    std::array<float, count> output{};
    auto engine = std::unique_ptr<IVectorMath>(createCPUMath());

    engine->allocate(count);
    engine->vectorAdd(a.data(), b.data(), output.data(), count);
    engine->free();

    for (float value : output) {
        EXPECT_NEAR(value, 3.0f, 1e-5f);
    }
}

TEST(CPUMath, ZeroElementsLeavesOutputUnchanged) {
    float a = 1.0f;
    float b = 2.0f;
    float output = 42.0f;
    auto engine = std::unique_ptr<IVectorMath>(createCPUMath());

    engine->allocate(1);
    engine->vectorAdd(&a, &b, &output, 0);
    engine->free();

    EXPECT_FLOAT_EQ(output, 42.0f);
}