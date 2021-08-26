object wat {

  var counter: Int = 0

  val l = Seq(1, 2, 3, 4, 5, 6)

  val f = l filter {
    counter += 1
    _ > 3
  }
}

object wat2 {

  var counter: Int = 0

  val l = Seq(1, 2, 3, 4, 5, 6)

  val f = l.filter { n => counter += 1; n > 3 }
}
