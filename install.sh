sudo apt-get install build-essential autoconf make cmake libtool
sudo apt-get install libuv1-dev zlib1g-dev openssl libssl-dev git

git clone https://github.com/uWebSockets/uWebSockets.git && cd uWebSockets
sudo make Linux
sudo make install
cd .. && rm -rf uWebSockets

git clone https://github.com/miloyip/rapidjson.git && cd rapidjson
mkdir build && cd build
cmake ..
sudo make
sudo make install
cd .. && cd ..
rm -rf rapidjson

sudo apt-get install libboost-all-dev
sudo apt-get install libmysqlcppconn-dev