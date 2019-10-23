#!/bin/sh
cd ..
docker run \
  --rm \
  -v $(pwd):/src \
  silkeh/clang:dev \
  /bin/bash -c "cd /src; rm -rf build; mkdir build; cd build; cmake -DIN3API=false -DIN3_LIB=false -DCMD=false -DUSE_CURL=false -DTEST=true -DCODE_COVERAGE=true -DUSE_SEGGER_RTT=false -DTRANSPORTS=false -DCMAKE_BUILD_TYPE=Debug ..  && make -j8 &&  make ccov-all && make ccov-all-report"
cd scripts