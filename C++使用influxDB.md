# C++ 使用InfluxDB API
## 环境准备
### mac环境安装influxDB
#### 安装
```shell script
brew update
sudo chown -R ${username} /usr/local/share/man/man8\
brew install influxdb
```
其中 `${username} `是本机的用户名。第二句必须执行，否则会因为权限问题安装失败
#### 启动
启动influxDB server
```shell script
influxd
```
启动client
```shell script
influx -host ${host} -port ${port}
```

`${host}` server的IP地址或域名， `${port}`端口号

如果是influxDB在本机可以直接用
```
influx
```

### mac安装Boost
Boost安装为可选项，如果不需要查询influxDB，可以不用安装

下安装包,由于从官网下载可能网速会很慢，所以在Google云盘放了一份：
https://drive.google.com/file/d/13UfAzH4Sz4EymUwunzFAHOtdeLSEcMV5/view?usp=sharing

官方下地址：https://sourceforge.net/projects/boost/files/boost/1.62.0/

根据自己的网速上面的地址二选一进行下载

下载完之后，解压后进入目录`boost_1_62_0`进行安装

```shell script
./bootstrap.sh
./b2
sudo ./b2 install
```

##如何使用C++开发
### 开发前的准备
安装influxDB C++库，以下两种方式二选一：

下载源码安装
```shell script
git clone https://github.com/awegrzyn/influxdb-cxx.git
cd influxdb-cxx; mkdir build
cd build
cmake ..
sudo make install
```

macOS 安装
```shell script
brew install awegrzyn/influxdata/influxdb-cxx
```

### 编码

写入DB
```c++
#include "../include/InfluxDBFactory.h"
  
  //创建influxdb使用对象
  auto influxdb = influxdb::InfluxDBFactory::Get("http://localhost:8086/?db=simple");
  //插入值
  influxdb->write(influxdb::Point{"demo_table"}
                        .addTag("user_id", "111")
                        .addTag("user_name", "Peter")
                        .addField("age", 12)
                        .addField("nike_name", "aaa"));
```

influx DB里的表不需要事先创建。表中的字段分为两种类型tag和value。tag是表的索引可以和timestamp唯一标识一条数据

查询DB
```C++
//创建influxdb使用对象,读写对象一点要分开，否则运行会报错
auto influxdbRead =
   influxdb::InfluxDBFactory::Get("http://localhost:8086?db=simple");

//查询现有DB数据
auto points = influxdbRead->query("SELECT * FROM demo_table where user_id='111' and user_name='Peter'");

//打印查询结果
std::cout << "get result size:" << points.size() << std::endl;
  for (auto &one_point : points) {
    std::cout << one_point.getFields() << std::endl;
    std::cout << one_point.getTags() << std::endl;
  }
```

###设置cmake编译
编译时要链接上curl的库

```cmake
find_package(CURL REQUIRED)
add_executable(simple_use simple_use.cc)
target_link_libraries(simple_use InfluxDB ${CURL_LIBRARIES} )
```

如果使用了查询功能则需要加上Boost库链接

```cmake

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR" )
find_package(CURL REQUIRED)
find_package(Boost REQUIRED)

add_executable(simple_use simple_use.cc)
target_link_libraries(simple_use InfluxDB ${CURL_LIBRARIES} ${Boost_LIBRARIES} )
```
























