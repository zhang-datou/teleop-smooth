/*
 * @Descripttion: 
 * @version: 
 * @Author: Zhangjianqing
 * @Date: 2020-03-13 15:54:52
 * @LastEditors: Zhangjianqing
 * @LastEditTime: 2020-03-13 17:26:37
 */

#pragma once
#include <iostream>
#include <queue>
#include <vector>
//IIR�˲���
class filter_iir
{
private:
    /* data */
    std::vector<double> num; //�˲�ϵ��
    std::vector<double> den;
    std::vector<double> trans_w; //��ʷֵ-����

public:
    filter_iir(/* args */);
    ~filter_iir();
    void clear();
    void init(std::vector<double> num, std::vector<double> den);
    double filter(double data);
};
