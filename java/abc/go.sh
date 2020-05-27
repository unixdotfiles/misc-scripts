javac c/C.java
javac -cp b b/B.java 
javac -cp a a/A.java ## exports B

# strict deps
javac -cp a:b T.java

# non-strict-deps

javac -cp a:b:c T.java
