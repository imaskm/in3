#!/bin/sh
mkdir -p build
cd build
rm -rf * 
export CTEST_OUTPUT_ON_FAILURE=1 
cmake -DEVM_GAS=true -DCMAKE_BUILD_TYPE=Release .. -DLIBCURL_TYPE=shared && make &&  make install
#cmake -DTEST=true -DEVM_GAS=true -DCMAKE_BUILD_TYPE=Debug .. && make && make test
#cmake -GNinja -DTEST=true -DCMAKE_BUILD_TYPE=Debug .. && ninja && ninja test
#cmake -DTEST=true -DEVM_GAS=true -GNinja -DCMAKE_BUILD_TYPE=Release .. && ninja
cd ..
