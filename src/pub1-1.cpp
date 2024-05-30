#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>
#include <functional>
using namespace std::chrono_literals;

void pub_callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub)
{
    auto message = std_msgs::msg::String();
    message.data = "Hello world!";
    RCLCPP_INFO(node->get_logger(), "node Publish: %s", message.data.c_str());
    pub->publish(message);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("mynode");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<std_msgs::msg::String>("mytopic", qos_profile);
    std::function<void()> fn = std::bind(pub_callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);    //타이머
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}