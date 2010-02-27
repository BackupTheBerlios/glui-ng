#!/bin/sh -x
tests0() { check ./GENERATED/PackingTest; }
tests1() { check ./GENERATED/SizeComputationTest; }
tests2() { check ./GENERATED/ContainerEventTest; }
tests3() { check ./GENERATED/WindowTest; }
tests4() { export GLUI_REPLAY_FILE='./eventsfiles/KeyboardTest.xevt'; check ./GENERATED/KeyboardTest; }
tests5() { check ./GENERATED/DrawingHelpsTest; }
tests_count=6

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

if [ -z "$1" ]; then
        #all tests
        i=0
        while [ $i -lt ${tests_count} ]; do
                tests${i}
                i=$((i+1))
        done
else
        tests${1}
fi


cd $OLDPWD

