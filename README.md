

## Cpp_Python_called

### 构建docker 虚拟环境

```BASH
docker run -dit \
  --name cpp_python_called \
  -e DISPLAY=$DISPLAY \
  -e PULSE_SERVER=unix:/mnt/wslg/PulseServer \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v /mnt/wslg/:/mnt/wslg/ \
  -v /home/me/data/cpp_python_called:/root/code \
  local_base_image:1.0 \
  /bin/bash
  
docker exec -it cpp_ptyhon_called /bin/bash
```

### 1.Python_Call_Cpp

> 项目地址：`\\wsl.localhost\Ubuntu\home\me\data\cpp_python_called/pyhton_call_cpp`

```bash
# 项目初始化
git init
git config --global --add safe.directory /root/code

# 采用git submodules方式，将pybind11作为子模块
# git submodule add -b stable https://github.com/pybind/pybind11.git externals/pybind11
# 直接下载到本地不能做为子模块，因为该源码目录不再是一个github项目，需要使用git clone下载到本地才行
# git submodule add -b stable ../pybind11-master/pybind11-master/  Externals/pybind11
git submodule update --init --recursive

#编译，构建python模块
mkdir build && cd build
cmake ..
make

# 安装python版本 pybind11
pip install pybind11

# python中需要添加 sys.path.append("/root/code/python_call_cpp/build") # 添加 C++ 库的路径
# 然后执行
python3 main.py
```

### 2. Cpp_Call_Python

> 项目地址：`\\wsl.localhost\Ubuntu\home\me\data\cpp_python_called/cpp_call_python`

```BASH
# 注意：这里没有再用git submodules方式，而是使用了find_package方法，以此证明两种方式都可行
# 首先需要安装pybind11库，然后在CMakeLists.txt中就可以直接使用find_package寻找
apt-get install python3-pybind11

# 其次构建一个py文件，里面添加待调用的函数，py文件名称就是Cpp寻找的模块名，需要保证与可执行文件在同一目录，不然找不到
touch main.py
...

# #编译，生成可执行文件
mkdir build && cd build
cmake ..
make

# 执行，这里是因为py文件在build上一级目录，所以要退出来，执行的过程才能找到这个py文件
cd ..
.build/main
```

### 总结

**主要就是依赖pybind11这个库**，python调用Cpp的，就需要安装`pip install pybind11`，保证了python中能够找到xx.so并正确解析为python模块。cpp调用python，就需要使用git submodules或者find_pakage的方式找到pybind11库(本地安装`apt-get install python3-pybind11`)，然后会自动找xx.py文件，并导入执行。