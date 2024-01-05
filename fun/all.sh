#!/bin/sh
set -x
# html
# Javascript
file poly.html
python2 poly.html
clang++ -w -x c poly.html && ./a.out
clang++ -w -trigraphs -x c poly.html && ./a.out
clang -w -x c++ poly.html && ./a.out
clang -w -trigraphs -x c++ poly.html && ./a.out
perl poly.html
perl6 poly.html
sh poly.html
zsh poly.html
bash poly.html
ruby poly.html
make -f poly.html
tclsh poly.html
wsc poly.html
ghc -w -x lhs poly.html 2>/dev/null && ./poly
bf2c < poly.html

rm poly a.out
