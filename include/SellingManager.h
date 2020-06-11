//
// Created by Mingfei Deng on 2020/6/11.
//

#ifndef GILEROSS_SELLINGMANAGER_H
#define GILEROSS_SELLINGMANAGER_H


#include <vector>
#include <iostream>

struct Selling {
  int selling_id; //商品id，唯一表示一个商品
  std::string selling_name; //商品名
  int sell_in; //过期天数
  int quality; //价值
  int sell_in_day; //已经买入天数
  int sell_type; //商品类型 0：普通商品  1：门票
};


class SellingManager {
public:
  SellingManager(){};
  virtual ~SellingManager(){};
  void AddSelling(const Selling& selling);
  std::vector<Selling> GetSellingList();
  void UpDate();

private:
  std::vector<Selling> selling_list;
};


#endif // GILEROSS_SELLINGMANAGER_H
