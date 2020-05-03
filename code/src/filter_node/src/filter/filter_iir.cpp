/*
 * @Descripttion: 
 * @version: 
 * @Author: Zhangjianqing
 * @Date: 2020-03-13 15:54:52
 * @LastEditors: Zhangjianqing
 * @LastEditTime: 2020-04-10 10:11:31
 */

#include "filter_iir.hpp"

filter_iir::filter_iir(/* args */)
{
}

filter_iir::~filter_iir()
{
}
void filter_iir::clear()
{
}
void filter_iir::init(std::vector<double> num_, std::vector<double> den_)
{
    num = num_;
    den = den_;
    // std::cout << num.size() << std::endl;
    // std::cout << num.size() << std::endl;
    std::vector<double> w_zero(std::max(num.size(), den.size()), 0);
    trans_w = w_zero;
}
double filter_iir::filter(double data)
{
    //更新输入
    double sum_w = 0;
    for (int i = 1; i < den.size(); i++)
    {
        sum_w += den[i] * trans_w[i];
    }
    trans_w[0] = data - sum_w;

    //计算输出
    double data_out = 0.0;
    for (int i = 0; i < num.size(); i++)
    {
        data_out += num[i] * trans_w[i];
    }

    //更新 w[n]
    for (int i = std::max(num.size(), den.size()) - 1; i >= 1; i--)
    {
        trans_w[i] = trans_w[i - 1];
    }
    return data_out;
}