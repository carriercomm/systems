#!/bin/bash

# save the command
app=./sl

make clean
make

echo " ---- test 1 ----"
$app 1
echo "----------------------------------------------------------"
echo ""
echo " ---- test 2 ----"
$app 2
echo "----------------------------------------------------------"
echo ""
echo " ---- test 3 ----"
$app 3
echo "----------------------------------------------------------"
echo ""
echo " ---- test 4 ----"
$app 4
echo "----------------------------------------------------------"
echo ""
echo " ---- test 5 ----"
$app 5
echo "----------------------------------------------------------"
echo ""
echo " ---- test 6 ----"
$app 6
echo "----------------------------------------------------------"
echo ""
echo " ---- test 7 ----"
$app 7
echo "----------------------------------------------------------"
echo ""
echo " ---- test 8 ----"
$app 8
echo "----------------------------------------------------------"
echo ""
echo " ---- test 9 ----"
$app 9
echo "----------------------------------------------------------"
echo ""
echo " ---- test 10 ----"
$app 10
echo "----------------------------------------------------------"
echo ""
echo " ---- test 11 ----"
$app 11
echo "----------------------------------------------------------"
echo ""
echo " ---- test 12 ----"
$app 12
echo "----------------------------------------------------------"
echo ""
echo " ---- test 13 ----"
$app 13
echo "----------------------------------------------------------"
echo ""
echo " ---- test 14 ----"
$app 14
echo "----------------------------------------------------------"
echo ""
echo " ---- test 15 ----"
$app 15
echo "----------------------------------------------------------"
echo ""

echo "----------------------------------------------------------"
echo " --- Finished --- "

exit 0
