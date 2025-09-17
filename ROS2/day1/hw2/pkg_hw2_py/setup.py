from setuptools import find_packages, setup

package_name = 'pkg_hw2_py'

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
    maintainer='geonhu',
    maintainer_email='geonhu@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': ['talker_script = pkg_hw2_py.publish:main', 'listener_script= pkg_hw2_py.subscribe:main'
        ],
    },
)
