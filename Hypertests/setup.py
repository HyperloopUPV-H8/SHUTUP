from setuptools import find_packages, setup

setup(
    name='Hypertest',
    packages=find_packages(),
    version='0.1.0',
    description='Shutup/python interface',
    author='Daniel González',
    license='MIT',
    install_requires=[],
    setup_requires=['pytest-runner'],
    tests_require=['pytest==4.4.1']
)