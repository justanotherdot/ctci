class Queue

  def initialize
    @in = []
    @out = []
  end

  def enqueue(val)
    @in << val
  end

  def dequeue
    if @out.empty?
      while not @in.empty?
        @out << @in.pop
      end
      @out.pop
    else
      @out.pop
    end
  end

  def to_s
    'in: ' + @in.to_s + ', out: ' + @out.to_s
  end
end

q = Queue.new
q.enqueue(1)
q.enqueue(2)
k = q.dequeue
puts k
puts q
