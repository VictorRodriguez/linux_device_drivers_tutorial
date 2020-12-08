#!/bin/bash

echo "hi there"

git clone --depth 1 https://github.com/torvalds/linux.git
cd /linux/ && yes "" | make oldconfig
cd /linux/ && make

