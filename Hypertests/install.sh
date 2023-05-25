yes | sudo pip uninstall Hypertest;
yes | sudo python3 setup.py bdist_wheel;
yes | sudo pip install ./dist/Hypertest-0.1.0-py3-none-any.whl;
yes | rm -r build/;
yes | rm -r dist/;
yes | rm -r .eggs/;
yes | rm -r Hypertest.egg-info/;