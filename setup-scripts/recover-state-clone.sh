#!/bin/sh

cd ~
git clone --recurse-submodules git@github.com:unixdotfiles/bin
git clone git@github.com:unixdotfiles/dotfiles .conf
mkdir -p ~/bin/submodules/go ~/svn ~/tmp

mkdir -p pcgen

for module in pcgen pcgen-base pcgen-formula pcgen-utilities
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
    git clone git@github.com:macports/macports-$module.git "$dirname"
    cd "$dirname"
    git remote add grimreaper git@github.com:grimreaper/$module.git
  )
done

mkdir -p fbsd/phacility

(
  cd fbsd/phacility
  git clone https://github.com/freebsd/phabricator.git "phabricator"
  cd phabricator
  git remote add upstream https://github.com/phacility/phabricator.git
)
