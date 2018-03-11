# Bubble sort with two stacks.

def sort(stack)
  if stack.size < 2
    return stack
  end

  tmp = []
  while !stack.empty?
    if tmp.empty?
      tmp << stack.pop
    else
      a = stack.pop
      b = tmp.pop

      # Put on bottom.
      while !tmp.empty? and a < b
        stack << b
        b = tmp.pop
      end

      if a < b
        tmp << a
        tmp << b
      else
        tmp << b
        tmp << a
      end

    end
  end

  # Top of stack is min.
  while !tmp.empty?
    stack << tmp.pop
  end

  return stack
end

xs = [9, 7, 2, 3, 1, 8, 4, 3]
ys = sort(xs.shuffle)
raise Exception unless xs != xs.sort
puts ys.to_s
