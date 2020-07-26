#!/usr/bin/bash

7z a -r src.zip src
7z a -r encode.zip encode
scp -i ~/.ssh/rsa_poly src.zip encode.zip cagiu@L4712-02.info.polymtl.ca:~/inf8601/lab2
ssh -i ~/.ssh/rsa_poly -X -Y cagiu@L4712-02.info.polymtl.ca "~/inf8601/lab2/run_server.sh"

