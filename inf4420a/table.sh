#!/bin/bash
rm tmp.txt
for a in {1..9}
	do
	for b in {1..9}
		do
			for c in {1..9}
			do
				for d in {1..9}
				do
					 python2.7 transBase.py "$a$b$c$d" >> tmp.txt	

				done
			done
		done
	done
exit
