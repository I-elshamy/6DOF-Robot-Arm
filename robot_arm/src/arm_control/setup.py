from setuptools import setup
import os
from glob import glob

package_name = 'arm_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
            glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ibrahim',
    maintainer_email='ibrahim@todo.todo',
    description='Arm control scripts',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
            'control_serial = arm_control.control_serial:main',
            'control_micro = arm_control.control_micro:main',
        ],
    },
)