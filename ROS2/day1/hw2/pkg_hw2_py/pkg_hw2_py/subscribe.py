import rclpy
from rclpy.node import Node
from std_msgs.msg import String,Int32 ,Float32

class PyListener(Node): #Node 상속, subscribe 구현
    def __init__(self):
        super().__init__('py_listener') #Node 인스턴스 생성 및 노드 네임 설정
        #subscribe 할 멤버 생성 및 콜백함수 설정
        self.sub_str = self.create_subscription(String, 'topicname', self.on_msg, 10)
        self.sub_int = self.create_subscription(Int32, 'int_topic', self.on_msg, 10)    
        self.sub_float = self.create_subscription(Float32, 'float_topic', self.on_msg, 10)  
        self.get_logger().info('PyListener up') #터미널에 한 번만 초기에 출력

    def on_msg(self, msg): #메시지 수신 시 호출되는 콜백함수
        self.get_logger().info("{0}, ".format(msg.data))


 # main 정의
def main():
    rclpy.init()
    node = PyListener() #객체 생성
    rclpy.spin(node) #노드가 종료될 때까지 돌아감
    node.destroy_node()
    rclpy.shutdown()
    
if __name__ == '__main__':
    main() #위에 정의한 main 함수 호출
