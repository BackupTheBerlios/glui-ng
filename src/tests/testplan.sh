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

check ./PackingTest
check ./SizeComputationTest
check ./ContainerEventTest
check ./GlutWindowTest

popd

