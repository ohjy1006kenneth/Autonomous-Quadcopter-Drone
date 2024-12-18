from setuptools import find_packages, setup

package_name = 'controls'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='juyoungoh',
    maintainer_email='ohjuyoung1006@gmail.com',
    description='Receive telemetry from drone and send control signals',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'controls_pub = controls.control_publisher:main',
            'arduino = controls.arduino:main',
        ],
    },
)
