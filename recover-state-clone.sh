#!/bin/sh

cd ~
git clone git@github.com:unixdotfiles/bin
git clone git@github.com:unixdotfiles/dotfiles .conf

mkdir -p ~/svn
mkdir -p pcgen

for module in pcgen pcgen-base pcgen-formula pcgen-gui3 pcgen-utilities
do
  modulename="${module#pcgen-}"
  dirname="${modulename:-pcgen}"
  (
    cd pcgen
    git clone https://github.com/PCGen/$module.git "$dirname"
    cd "$dirname"
    git remote add grimreaper git@github.com:grimreaper/$module.git
  )
done

mkdir -p macports

for module in macports-base macports-ports
do
  modulename="${module#macports-}"
  dirname="${modulename}"
  (
    cd macports
    git clone git@github.com:macports:$module.git "$dirname"
    cd "$dirname"
    git remote add grimreaper git@github.com:grimreaper/$module.git
  )
done

mkdir -p fbsd/phacility

for module in libphutil phabricator
do
  modulename="${module}"
  dirname="${modulename}"
  (
    cd fbsd/phacility
    git clone https://github.com/freebsd/$module.git "$dirname"
    cd "$dirname"
    git remote add upstream https://github.com/phacility/$module.git
  )
done
