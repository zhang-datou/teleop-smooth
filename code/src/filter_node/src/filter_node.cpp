/*
 * @Descripttion: 
 * @version: 
 * @Author: Zhangjianqing
 * @Date: 2020-05-01 22:00:45
 * @LastEditors: Zhangjianqing
 * @LastEditTime: 2020-05-03 19:00:56
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

#include "ros/ros.h"
#include "tf/tf.h"

#include "filter_iir.hpp"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include <geometry_msgs/Pose2D.h>

using namespace std;

class filter_node
{
public:
    filter_node()
    {
        ros::NodeHandle nh;
        filter_init();
        _cmd_sub = nh.subscribe("cmd_vel", 10, &filter_node::cmd_callback, this);
        timer = nh.createTimer(ros::Duration(0.001), &filter_node::timer_callback, this);

        _vel_pub = nh.advertise<geometry_msgs::Twist>("vel", 10);
    }

private:
    void filter_init()
    {
        double T = 0.001;
        double w_v = 5;  //¹ÌÓÐÆµÂÊ
        double w_w = 10; //¹ÌÓÐÆµÂÊ
        // double k = 1;  //×èÄá±È£¬ÁÙ½ç×èÄá
        double tmp1 = exp(-T * w_v);
        double k1 = (1 - tmp1) * (1 - tmp1);
        filter_v.init({k1, 0}, {1, -2 * tmp1, tmp1 * tmp1});

        double tmp2 = exp(-T * w_w);
        double k2 = (1 - tmp2) * (1 - tmp2);
        filter_w.init({k2, 0}, {1, -2 * tmp2, tmp2 * tmp2});
    }
    //Ò£¿Ø
    void cmd_callback(const geometry_msgs::Twist msg)
    {
        vel = msg.linear.x;
        anglevel = msg.angular.z;
    }

    void timer_callback(const ros::TimerEvent &)
    {
        vel_pub.linear.x = filter_v.filter(vel);
        vel_pub.angular.z = filter_w.filter(anglevel);
        _vel_pub.publish(vel_pub);
    }

    //timer
    ros::Timer timer;
    //filter
    filter_iir filter_v;
    filter_iir filter_w;

    double vel;      //m/s
    double anglevel; //rad/s

    geometry_msgs::Twist vel_pub;

    // Subscribers
    ros::Subscriber _cmd_sub;

    // publishers
    ros::Publisher _vel_pub;
};

int main(int argc, char *argv[])
{
    //ros init
    ros::init(argc, argv, "filter_node");
    filter_node filter_node;
    ros::spin();
    return 0;
}