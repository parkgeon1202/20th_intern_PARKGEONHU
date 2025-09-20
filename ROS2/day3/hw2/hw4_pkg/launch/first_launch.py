
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():


    return LaunchDescription([
        Node(
            package="hw4_pkg",
            executable="publish_node",
            name="publish_node"
        ),
        Node(
            package="hw4_pkg",
            executable="subscribe_node",
            name="subscribe_node",
            parameters=["/home/geonhu/colcon_ws/src/hw4_pkg/config/params.yaml"]
        ),
        Node(
            package="pkg_hw3_cpp",
            executable="publisher",
            name="publisher"
        )
    ])
