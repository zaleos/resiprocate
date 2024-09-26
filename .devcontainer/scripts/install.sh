#!/bin/bash
autoreconf --install
./configure --with-repro
make && sudo make install