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

check ./GENERATED/bin/PackingTest
check ./GENERATED/bin/SizeComputationTest
check ./GENERATED/bin/ContainerEventTest
check ./GENERATED/bin/GlutWindowTest
check ./GENERATED/bin/GlutKeyboardTest
check ./GENERATED/bin/DrawingHelpsTest

popd

