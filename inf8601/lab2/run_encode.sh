#!/usr/bin/bash

cd ~/inf8601/lab2 && 7z x src.zip -aoa && 7z x encode.zip -aoa && make && ./encode/encode