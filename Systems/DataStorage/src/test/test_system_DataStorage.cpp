

#include <IDataStorageSystem.hpp>

#include <BaseDataStorageSystem.hpp>

#include <DummyDataStorageSystem/DummyDataStorageSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgDataStorage, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::DataStorageSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IDataStorageSystem {
public:
};
TEST(DataStorageSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseDataStorageSystem {
public:
};
TEST(DataStorageSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests