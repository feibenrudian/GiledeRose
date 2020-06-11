//
// Created by Mingfei Deng on 2020/6/11.
//
#include "../include/SellingManager.h"
void SellingManager::AddSelling(const Selling &selling) {
  selling_list.push_back(selling);
}

std::vector<Selling> SellingManager::GetSellingList() { return selling_list; }

void SellingManager::UpDate() {
  for (auto &one_selling : selling_list) {

    //普通商品
    if (0 == one_selling.sell_type) {
      //
      if (one_selling.sell_in > one_selling.sell_in_day) {
        //每天价值1点下滑
        one_selling.quality -= 1;
      } else {
        //过期后加倍下滑
        one_selling.quality -= 2;
      }

      //不能小于0
      one_selling.quality = (one_selling.quality < 0) ? 0 : one_selling.quality;
    }

    //演出票
    if (1 == one_selling.sell_type) {

      int life_day = one_selling.sell_in - one_selling.sell_in_day;
      if (life_day > 10) {
        // 10天以前每天价值每天上升1点
        one_selling.quality += 1;
      } else if (life_day > 5) {
        // 10天到5天，价值每天上升2
        one_selling.quality += 2;
      } else if (life_day >= 0) {
        // 5天以内，价值每天上升3
        one_selling.quality += 3;
      } else {
        one_selling.quality = 0;
      }
    }

    //储存天数增加
    one_selling.sell_in_day++;
  }
}
