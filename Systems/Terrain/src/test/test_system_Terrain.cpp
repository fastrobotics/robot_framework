

#include <ITerrainSystem.hpp>

#include <BaseTerrainSystem.hpp>

#include <DummyTerrainSystem/DummyTerrainSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgTerrain, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::TerrainSystem;
// System Interface Tests
class TestConcreteSystemInterface : public ITerrainSystem {
public:
};
TEST(TerrainSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseTerrainSystem {
public:
};
TEST(TerrainSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests