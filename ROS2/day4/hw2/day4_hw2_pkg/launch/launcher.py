
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():


    return LaunchDescription([
        Node(
            package="day4_hw2_pkg",
            executable="control",
            name="sub_and_pub"
        ),
        Node(
            package="day4_hw2_2_pkg",
            executable="for_control",
            name="control_node"
        ),
        Node(
            package="joy",
            executable="joy_node",
            name="joy_node"
        )
    ])