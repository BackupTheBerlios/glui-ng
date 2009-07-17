#!/bin/sh

check() {
    $1 && echo $1 SUCCESS && return 0
    echo $1 FAILED
    return 1
}

echo ${0}
dir=${0%/*}
echo ${dir}
pushd ${dir}

check ./GENERATED/PackingTest
check ./GENERATED/SizeComputationTest
check ./GENERATED/ContainerEventTest
check ./GENERATED/GlutWindowTest
check ./GENERATED/GlutKeyboardTest
check ./GENERATED/DrawingHelpsTest

popd

