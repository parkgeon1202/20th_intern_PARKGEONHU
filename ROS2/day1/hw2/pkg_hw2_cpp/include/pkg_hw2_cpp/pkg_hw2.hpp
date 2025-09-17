#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/float32.hpp>
class MyCppNode : public rclcpp::Node{
 public:
      MyCppNode();
 private:
      rclcpp::TimerBase::SharedPtr timer_;
      void timer_callback();
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mycpp_publisher_;     
      rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr mycpp_publisher_int;
      rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr mycpp_publisher_float;          
      int count_ =1;



};
class subscribe_node: public rclcpp::Node{
     rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mycpp_subscriber_;  
     rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr mycpp_subscriber_int;
     rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr mycpp_subscriber_float;   
     void topic_callback_str(const std_msgs::msg::String::SharedPtr msg);
     void topic_callback_int(const std_msgs::msg::Int32::SharedPtr msg);
     void topic_callback_float(const std_msgs::msg::Float32::SharedPtr msg);
     public:
     subscribe_node();
};

