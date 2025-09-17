import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import Int32
from std_msgs.msg import Float32

class PyTalker(Node):
    def __init__(self):
        super().__init__('py_talker') #Node 인스턴스 생성 및 노드 네임 설정

        #퍼블리셔 할 멤버 생성
        self.pub_string = self.create_publisher(String, 'topicname', 10) 
        self.pub_int = self.create_publisher(Int32, 'int_topic', 10)
        self.pub_fl = self.create_publisher(Float32, 'float_topic', 10)
        self.timer = self.create_timer(1.0, self.on_timer) #1초마다 on_timer 호출되도록 설정
        self.count = 0
        self.get_logger().info('PyTalker up') #터미널에 한 번만 초기에 출력
     
    def on_timer(self):
        #메시지 생성
        msg = String()
        num = Int32()
        fl= Float32()
        msg.data = f'Hello World_py: {self.count}' 
        num.data = 9000
        fl.data = 0.89
        self.count += 1
        #터미널에 매번 출력
        self.get_logger().info(f'Published: str: {msg.data}, num: {num.data}, float: {fl.data}')
        #메시지 발행
        self.pub_string.publish(msg)
        self.pub_fl.publish(fl)
        self.pub_int.publish(num)
#main 정의
def main():
    rclpy.init()
    node = PyTalker() #객체 생성
    rclpy.spin(node) #노드가 종료될 때까지 돌아감
    node.destroy_node()
    rclpy.shutdown()
    
if __name__ == '__main__':
    main() #위에 정의한 main 함수 호출
