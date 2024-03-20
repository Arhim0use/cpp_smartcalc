#include "s21_smartcalc_test.h"

namespase s21{

void s21ContainersMapTest::SetUp() {
  s21_map = new map<int, std::string>;
  s21_map->insert({1, "one"});
  s21_map->insert({2, "two"});
  s21_map->insert({3, "three"});
  s21_map->insert({4, "four"});
  s21_map->insert({5, "five"});

  std_map = new std::map<int, std::string>;
  std_map->insert({1, "one"});
  std_map->insert({2, "two"});
  std_map->insert({3, "three"});
  std_map->insert({4, "four"});
  std_map->insert({5, "five"});
}

void s21ContainersMapTest::TearDown() {
  delete std_map;
  delete s21_map;
}


TEST_F(s21ContainersMapTest, SpeedTest) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  random_insert(5000, 100099, s21_map, std_map);
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ((s21_map.begin()->first), (std_map.begin()->first));
  EXPECT_EQ((s21_map.begin()->second), (std_map.begin()->second));
}

TEST_F(s21ContainersMapTest, DefaultConstructorTest) {
  std::map<std::string, int> def;
  map<std::string, int> custom;
  EXPECT_EQ(def.size(), 0);
  EXPECT_EQ(def.size(), custom.size());
}

TEST_F(s21ContainersMapTest, ConstructorInitializerListTest) {
  s21::map<int, std::string> s21_map_temp{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  EXPECT_EQ("one", s21_map_temp.at(1));
  EXPECT_EQ("two", s21_map_temp.at(2));
  EXPECT_EQ("three", s21_map_temp.at(3));
  EXPECT_EQ("four", s21_map_temp.at(4));
  EXPECT_EQ("five", s21_map_temp.at(5));
}
} // namespace s21



int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
