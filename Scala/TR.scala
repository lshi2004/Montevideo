trait Ord {
      def <(that: Any): Boolean
      def <=(that: Any): Boolean = (this < that) || (this == that)
      def >(that: Any): Boolean = !(this <= that)
      def >=(that: Any): Boolean = !(this < that)
}


class Date(y: Int, m: Int, d: Int) extends Ord {
      def year = y
      def month = m
      def day = d

      override def toString(): String = year + "-" + month + "-" + day

      override def equals(that: Any): Boolean =
      	       this.isInstanceOf[Date] && {
	           val o = that.asInstanceOf[Date]
		   o.day == day && o.month == month && o.year == year
	       }

      def <(that: Any): Boolean = {
      	  if (!that.isInstanceOf[Date])
	     sys.error("cannot compare " + that + "and a Date")

	  val o = that.asInstanceOf[Date]
	  (year < o.year) || (year == o.year && (month < o.month ||
	  	(month == o.month && day < o.day)))
      }
}


object TR {
       def main(args: Array[String]) {
       	   val d1 = new Date(1984, 1, 1)
	   val d2 = new Date(2001, 3, 4)
	   val d3 = new Date(2004, 1, 4)
	   println("d1 d2 " + (d1 < d2) + " and d3 d2 " + (d2 > d3) )
       	   println("Hello World \n")
	   
       } 
       
}