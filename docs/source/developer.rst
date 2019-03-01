.. _developer:

C++ 开发者指南
===============

.. note::

    为了顺利编译代码， 请勿使用从 github 直接下载源码包的方式编译。 原因是 git 上传时部分文件的换行符被置换为Linux式的换行符，将导致直接下载的部分代码在Windows下无法顺利编译。

C++ API参考：`<http://fasiondog.cn/hikyuu/cpp_ref/index.html>`_。

C++测试工程参考：`<http://fasiondog.cn/hikyuu/test_doc/index.html>`_


编译前准备
----------------

1、安装C++编译器
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Windows 平台：Visual C++ 2017 (或以上）
- Linux 平台: g++ > = 5.4.0 、 clang++ >= 3.8.0


2、安装构建工具 xmake
^^^^^^^^^^^^^^^^^^^^^^^^^^^

xmake >= 2.2.2，网址：`<https://github.com/xmake-io/xmake>`_

Windows下，从 xmake github 页面中的“release”进入，直接下载相应的 exe 安装包安装即可：

.. figure:: _static/dev-001.jpg


Linux、macOSX 执行以下指令安装：

.. code-block:: shell

    git clone --branch=dev https://github.com/tboox/xmake.git tboox/xmake --depth 1
    cd ./tboox/xmake
    ./scripts/get.sh __local__


3、克隆 Hikyuu 源码
^^^^^^^^^^^^^^^^^^^^^^^^

执行以下命令克隆 hikyuu 源码：（请勿在中文目录下克隆代码）

.. code-block:: shell

    git clone https://github.com/fasiondog/hikyuu.git --recursive --depth 1    


4、下载 Boost 源码
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. 下载 Boost 源码 `<http://www.boost.org>`_ 
2. 将下载的 boost 源码包解压至上一步中克隆的 hikyuu目录下，如下图所示：

.. figure:: _static/dev-002.jpg
    
.. note::

    以下版本的 boost 无法顺利编译，请注意注意不要使用：
    
    - Windows：1.67
    - linux、macOS：1.68
    
5、Linux下安装依赖软件包
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Linux下需安装依赖的开发软件包：hdf-dev、mysqlclient。如 Ubuntu 下，执行以下命令：

.. code-block:: shell
    
    sudo apt-get install -y libhdf5-dev libhdf5-serial-dev libmysqlclient-dev    
    

编译与安装
------------

直接在克隆的 hikyuu 目录下执行 python setup.py 即可：

- python setup.py help        -- 查看帮助
- python setup.py             -- 执行编译（同build参数）
- python setup.py build       -- 执行编译（编译后，可在本地 hikyuu 目录下引用 hikyuu 包。如希望在其他目录下可使用，需执行安装）
- python setup.py install     -- 执行安装（安装到 python 的 site-packages 目录下）
- python setup.py uninstall   -- 删除已安装的Hikyuu
- python setup.py clear       -- 清除本地编译结果
- python setup.py bdist_wheel -- 生成wheel安装包


