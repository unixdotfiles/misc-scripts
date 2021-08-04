#!/bin/sh

javac ExampleEnumJava.java
scalac ExampleEnumScala.scala

javap ExampleEnumJava
javap ExampleEnumScala

javap -v xampleEnumJava | head
javap -v ExampleEnumScala | head
