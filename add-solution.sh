#! /bin/sh

if [ $# -ne 2 ]; then
	echo "Usage: $0 <problem-name> <problem-difficulty>" >&2
	exit 1
fi

problem_name=$1
problem_difficulty=$2

dir=`dirname $0`
cp -rv $dir/solutions/template $dir/solutions/$problem_name
ln -sv ../../solutions/$problem_name $dir/by-difficulty/$problem_difficulty
