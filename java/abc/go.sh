set -x

echo strict deps
javac c/C.java
javac -cp c b/B.java
javac -cp b a/A.java ## exports B
javac -cp a:b T.java

echo non-strict-deps
javac c/C.java
javac -cp c b/B.java
javac -cp b:c a/A.java ## exports B
javac -cp a:b:c T.java
