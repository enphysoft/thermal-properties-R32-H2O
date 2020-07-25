#!/bin/bash
#+TITLE: setup.sh
#+File: /home/albertsk/CEPL/CEPL2020/resources/refprop2309/tst/cpp-fit-tp-H2O-R32/publish/setup.sh
#+Date: Sat Jul 25 10:52:55 HST 2020
#+Author: Albert S. Kim, albertsk@hawaii.edu
#
#
. ~/.bashrc 
# . /opt/openfoam5/etc/bashrc

cp ../*.cpp ./
cp ../*.h ./
cp ../Makefile ./
make 
exit 0


