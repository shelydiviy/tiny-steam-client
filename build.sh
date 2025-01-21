#!/bin/bash

HL2SDK_DIR="/home/sprut/fake/hl2sdk"
ASIO_DIR="/home/sprut/asio/asio"
CRYPTOPP_DIR="/home/sprut/fake/cryptopp-CRYPTOPP_8_7_0"

cmake -DCMAKE_BUILD_TYPE=Release -DHL2SDK-CSGO:PATH=$HL2SDK_DIR -DASIO-SRC:PATH=$ASIO_DIR -DCRYPTOPP-SRC:PATH=$CRYPTOPP_DIR -DEXECUTABLE_OUTPUT_PATH=$PWD/build/Release
make
