#!/bin/sh

javac ExampleEnumJava.java
scalac ExampleEnumScala.scala

javap ExampleEnumJava
javap ExampleEnumScala

