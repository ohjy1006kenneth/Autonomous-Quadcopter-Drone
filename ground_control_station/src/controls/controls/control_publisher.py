import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from sensor_msgs.msg import Joy
import serial

class controlPublisher(Node):

    def __init__(self):
        super().__init__('control_publisher')
        
        # Define global variables
        self.yaw = 0
        self.throttle = 0
        self.roll = 0
        self.pitch = 0
        
        # Initialize serial connection
        self.serial_port = serial.Serial("/dev/ttyACM1", 115200, timeout=1)
        
        # Subscribers
        self.subscription = self.create_subscription(
            Joy,
            '/joy',
            self.joystick_callback,
            10)
        self.subscription  # prevent unused variable warning
        
        # Publisher
        self.controlPub = self.create_publisher(String, '/cmd_drone', 10)
    
    # Joystick Callback Function (Get Input from xbox controller, and send it over the serial port)
    def joystick_callback(self, msg):
        axes = msg.axes
        buttons = msg.buttons
        
        self.yaw = axes[0]
        self.throttle = axes[1]
        self.roll = axes[3]
        self.pitch = axes[4]
        
        msg = String()
        msg.data = "\nYaw: %s\nThrottle: %s\nRoll: %s\nPitch: %s\n" % (self.yaw, self.throttle, self.roll, self.pitch)
        self.controlPub.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        
        # Send msg.data over the serial connection to Arduino Nano
        self.serial_port.write(msg.data.encode('utf-8'))
        
        


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
