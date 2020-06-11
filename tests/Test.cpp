#include <gtest/gtest.h>
#include "../include/SellingManager.h"
using namespace std;

TEST(template, add_new_sell) {
  Selling selling{1, "rose", 10, 20, 0, 0};
  SellingManager manager;

  manager.AddSelling(selling);

  auto selling_list = manager.GetSellingList();

  EXPECT_EQ(1, selling_list[0].selling_id);
  EXPECT_EQ("rose", selling_list[0].selling_name);
  EXPECT_EQ(10, selling_list[0].sell_in);
  EXPECT_EQ(20, selling_list[0].quality);
  EXPECT_EQ(0, selling_list[0].sell_in_day);
  EXPECT_EQ(0, selling_list[0].sell_type);
}

TEST(template, normal_sell_one_day) {

  Selling selling{1, "rose", 10, 20, 0, 0};
  SellingManager manager;
  manager.AddSelling(selling);
  manager.UpDate();
  auto selling_list = manager.GetSellingList();

  EXPECT_EQ(1, selling_list[0].selling_id);
  EXPECT_EQ("rose", selling_list[0].selling_name);
  EXPECT_EQ(10, selling_list[0].sell_in);
  EXPECT_EQ(19, selling_list[0].quality);
  EXPECT_EQ(1, selling_list[0].sell_in_day);
  EXPECT_EQ(0, selling_list[0].sell_type);
}

TEST(template, normal_sell_out_time) {

  Selling selling{1, "rose", 10, 20, 0, 0};
  SellingManager manager;
  manager.AddSelling(selling);
  for (int i = 0; i < 11; i++ ){
    manager.UpDate();
  }

  auto selling_list = manager.GetSellingList();

  EXPECT_EQ(1, selling_list[0].selling_id);
  EXPECT_EQ("rose", selling_list[0].selling_name);
  EXPECT_EQ(10, selling_list[0].sell_in);
  EXPECT_EQ(8, selling_list[0].quality);
  EXPECT_EQ(11, selling_list[0].sell_in_day);
  EXPECT_EQ(0, selling_list[0].sell_type);
}

TEST(template, ticket_sell_oneday) {

  Selling selling{2, "football ticket", 15, 20, 0, 1};
  SellingManager manager;
  manager.AddSelling(selling);

  manager.UpDate();


  auto selling_list = manager.GetSellingList();

  EXPECT_EQ(2, selling_list[0].selling_id);
  EXPECT_EQ("football ticket", selling_list[0].selling_name);
  EXPECT_EQ(15, selling_list[0].sell_in);
  EXPECT_EQ(21, selling_list[0].quality);
  EXPECT_EQ(1, selling_list[0].sell_in_day);
  EXPECT_EQ(1, selling_list[0].sell_type);
}



