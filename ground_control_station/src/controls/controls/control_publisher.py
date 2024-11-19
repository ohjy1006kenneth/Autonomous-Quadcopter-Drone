import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from sensor_msgs.msg import Joy


class controlPublisher(Node):

    def __init__(self):
        super().__init__('control_publisher')
        
        # Define global variables
        self.yaw = 0
        self.throttle = 0
        self.roll = 0
        self.pitch = 0
        
        
        
        # Subscribers
        self.subscription = self.create_subscription(
            Joy,
            '/joy',
            self.joystick_callback,
            10)
        self.subscription  # prevent unused variable warning
        
        # Publisher
        self.controlPub = self.create_publisher(String, '/cmd_drone', 10)

    # Joystick Callback Function (Get Input from xbox controller, and publish as cmd_drone)
    def joystick_callback(self, msg):
        axes = msg.axes
        buttons = msg.buttons
        
        self.yaw = self.parse_input(-axes[0])
        self.throttle = self.parse_input(axes[1])
        self.roll = self.parse_input(-axes[3])
        self.pitch = self.parse_input(axes[4])
        
        msg = String()
        msg.data = "\nYaw: %d\nThrottle: %d\nRoll: %d\nPitch: %d\n" % (self.yaw, self.throttle, self.roll, self.pitch)
        self.get_logger().info(msg.data)
        self.controlPub.publish(msg)
    
    # Helper function to parse xbox controller input to percentage
    def parse_input(self, input):
        return (input + 1) * 50
        
        


def main(args=None):
    rclpy.init(args=args)

    control_publisher = controlPublisher()

    rclpy.spin(control_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    controlPublisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
