import rclpy
import pyudev
import serial
from rclpy.node import Node

from std_msgs.msg import String


class Arduino(Node):

    def __init__(self):
        super().__init__('arduino')
        self.subscription = self.create_subscription(
            String,
            '/cmd_drone',
            self.cmd_subscriber,
            10)
        self.subscription  # prevent unused variable warning
        
        
        # Initialize serial connection
        device_node = self.detect_arduino_usb()
        self.serial_port = serial.Serial(device_node, 9600, timeout=1)
        
        self.timer = self.create_timer(1, self.print_arduino_data)

    def cmd_subscriber(self, msg):
        # Send msg.data over the serial connection to Arduino Nano]
        msg.data = "test"
        self.serial_port.write(msg.data.encode('utf-8'))
            
    def print_arduino_data(self):
        # Check if there is data available on the serial port
        if self.serial_port.in_waiting > 0:
            try:
                incoming_data = self.serial_port.readline().decode('utf-8').strip()
                self.get_logger().info('"%s"' % incoming_data)
            except UnicodeDecodeError:
                self.get_logger().info('')

    # Helper function to detect the USB port that the xbox controller is connected to
    def detect_arduino_usb(self):
        context = pyudev.Context()
        devices = context.list_devices(subsystem='tty')
        for device in devices:
            device_node = device.device_node
            device_name = device.get('ID_MODEL')
            if 'ttyACM' in device_node and 'Arduino' in device_name:
                print(f"Device found: {device_name}")
                print(f"Device Node: {device_node}")
                return str(device_node)
        self.get_logger().info("Arduino not found")
        return None
    
def main(args=None):
    rclpy.init(args=args)

    arduino = Arduino()

    rclpy.spin(arduino)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    arduino.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()