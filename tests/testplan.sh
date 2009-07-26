#!/bin/sh

check() {
    $1 && echo $1 SUCCESS && return 0
    echo $1 FAILED
    return 1
}

echo ${0}
dir=${0%/*}
echo ${dir}
OLDPWD=$PWD
cd ${dir}

check ./GENERATED/PackingTest
check ./GENERATED/SizeComputationTest
check ./GENERATED/ContainerEventTest
check ./GENERATED/WindowTest
check ./GENERATED/KeyboardTest
check ./GENERATED/DrawingHelpsTest

cd $OLDPWD

