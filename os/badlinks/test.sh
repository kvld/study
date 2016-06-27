#!/usr/bin/env bash

DIR=hw2-example

rm -rf $DIR
mkdir $DIR

pushd $DIR

gtouch good-new-file
gtouch -m -d '2 month ago' good-old-file
ln -s good-new-file good-new-link

ln -s good-old-file good-old-link
gtouch -m -d '1 year ago' good-old-link

ln -s $RANDOM$RANDOM$RANDOM bad-new-link
ln -s $RANDOM$RANDOM$RANDOM bad-old-link
gtouch -m --no-dereference -d '2 weeks ago' bad-old-link

mkdir nested
pushd nested
ln -s $RANDOM$RANDOM$RANDOM bad-old-link2
gtouch -m --no-dereference -d '2 weeks ago' bad-old-link2
popd

ln -s nested link-to-nested

popd
