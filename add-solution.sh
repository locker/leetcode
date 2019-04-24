#! /bin/sh

if [ $# -lt 2 ]; then
	echo "Usage: $0 <name> <difficulty> [<tag>,...]" >&2
	exit 1
fi

problem_name=$1
problem_difficulty=$2
problem_tags=$3

dir=`dirname $0`
cp -rv $dir/solutions/template $dir/solutions/$problem_name
ln -sv ../../solutions/$problem_name $dir/by-difficulty/$problem_difficulty

for tag in `echo $problem_tags | tr , \\\n`; do
	mkdir -pv $dir/by-tag/$tag
	ln -sv ../../solutions/$problem_name $dir/by-tag/$tag
done
