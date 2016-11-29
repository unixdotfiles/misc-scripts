#!/bin/sh

for repo in ~/bin ~/misc-scripts ~/.conf
do
  (
    cd "$repo"
    git pull --rebase
  )
done
