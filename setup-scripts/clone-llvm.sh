#!/bin/sh

set -e

svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

(cd llvm/tools &&
  svn co http://llvm.org/svn/llvm-project/cfe/trunk clang)

(cd llvm/tools/clang/tools &&
  svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra)

(cd llvm/tools &&
  svn co http://llvm.org/svn/llvm-project/lld/trunk lld)

(cd llvm/tools &&
  svn co http://llvm.org/svn/llvm-project/polly/trunk polly)

(cd llvm/projects &&
  svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt)

(cd llvm/projects &&
  svn co http://llvm.org/svn/llvm-project/openmp/trunk openmp)

(cd llvm/projects &&
  svn co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx &&
  svn co http://llvm.org/svn/llvm-project/libcxxabi/trunk libcxxabi)

(cd llvm/projects &&
  svn co http://llvm.org/svn/llvm-project/test-suite/trunk test-suite)
