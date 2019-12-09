# IoT2020
ORE and wildcard based middlebox
# Privacy-preserving Packet Header Checking over In-the-Cloud Middleboxes
## Introduction:
This work introduces a middlebox system that can perform encrypted header matching based network functions. It leverages the latest practical primitives for search over encrypted data, i.e., searchable symmetric encryption (SSE) ,order-revealing encryption (ORE) and wildcard based Fuzzy Searchable Encryption(FSE). To mitigate recent inference attacks on ORE schemes, this work protects the order information during header matching inspection, and presents a rule-aware size reduction technique to achieve better performance.

#Publication:
Yu Guo, Cong Wang, Xingliang Yuan, and Xiaohua Jia, "Enabling Privacy-Preserving Header Matching for Outsourced Middleboxes", In the 26th IEEE/ACM International Symposium on Quality of Service (IWQoS’18).


## Installation:
Environment setup:

```shell
 * apt-get update
 * apt-get install gcc g++ libssl-dev libgmp-dev make cmake libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libevent-dev automake libtool flex bison pkg-config libglib2.0-dev git
 * apt-get install libmsgpack-dev libboost-thread-dev libboost-date-time-dev libboost-test-dev libboost-filesystem-dev libboost-system-dev libhiredis-dev cmake build-essential libboost-regex-dev
```

Thrift installation:
 
```shell
 * wget http://apache.communilink.net/thrift/0.9.2/thrift-0.9.2.tar.gz
 * tar zxvf 
 * cd thrift-0.9.2
 * ./configure
 * make
 * make install
```

Redis installation:

```shell
 * wget http://download.redis.io/releases/redis-3.2.0.tar.gz
 * tar zxvf redis-3.2.0.tar.gz
 * cd redis-3.2.0
 * ./configure
 * make
 * make install
 ```

redis3m (a C++ Redis client) installation:

```shell
 * git clone https://github.com/luca3m/redis3m
 * cd redis3m
 * cmake .
 * make
 * make install
```

