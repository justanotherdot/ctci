#!/usr/bin/env python3

"""
The caveat with this module is that it is very 2-dimensional centric.

Ideally we'd be able to handle any n-dimensional matrix for this functionality.
"""

from copy import deepcopy

class Matrix:
    "n by m matrix"

    def __init__(self, arr):
        if self.from_arr(arr):
            self.n, self.m = self.calculate_dims(arr)
        else:
            """
            A Rant (in One Docstring).

            Exceptions in library code make for lessened confidence that things
            won't 'go wrong' in produciton. 'go wrong' could mean two things:

            * The exception causes a crash or a crash-loop, causing service disruptions
            * The code fails in some way (pure or impure), silently, and the
              system slumps into a degraded state, causing problems, potentially
              catostrophically (silently deleting information from some
              persistent store or some such)

            Exceptions have their place; in a certain way they are like
            assertions that can be manipulated and integrated into a programs
            control flow. This is both good and bad. Asserts are an attempt to
            _try_ to catch things statically, but asserts should truly be
            treated as panics, and my argument here is that exceptions are no
            different in this class of error handling.

            Monads are an interesting case in point: If something goes wrong,
            some 'sticky' state gets tumbled into the mix, e.g. a Left or a
            Nothing. We can choose to introspect on the error values and do
            something different or we can allow the value to percolate back to
            the root of the program's execution (imagining the entry point of a
            program to be the root and the subsequent stack traces being the
            branches and leaves).

            In general, one needs to be careful about stuff like this below.
            An imagined scenario:

            - Someone is making a bunch of arrays in processing code. They
            don't know that this will raise an exception and as such provide no
            try-catch for it. They also don't test thoroughly and try to see
            what happens when invalid arrays are passed to the constructor
            here. When they roll this code out to production, there is some bad
            data that is now causes this line to throw this specific exception,
            and we've wasted time finding the disruption, correcting it, and
            rolling the change back out (including cauterizing the problem to
            lessen the impact on real users).

            If this code had returned a pure value, it's possible that our results
            of some computation(s), say, would be horribly wrong, which is also bad.

            One could try to argue that this scenario I described is a case
            where we'd ideally want there to be more testing for confidences'
            sake, and while I agree about that, I also think it's important to
            go the pure route that has some monadic characteristics to it;
            forcing explicit handling of error values is important and it means
            there is some static as well as runtime gurantees going on!

            """
            raise Exception('Unknown array type passed to Matrix')

    def init_matrix(self, n, m, default=0):
        self.n = n
        self.m = m
        self._ref = [[]]*self.n
        for i in range(self.n):
            self._ref[i] = [default]*self.m

    def calculate_dims(self, arr):
        n, m = 0, 0
        n = len(arr)
        if n > 0:
            m = len(arr[0])
        return n, m

    def set(self, i, j, val):
        if i >= self.n or j >= self.m:
            return False
        self._ref[i][j] = val;
        return True

    def to_string(self):
        s = "["
        for i in range(self.n):
            s += "\n [" if i == 0 else " ["
            for j in range(self.m):
                if j+1 == self.m:
                    s += str(self._ref[i][j])
                else:
                    s += str(self._ref[i][j]) + " "
            if i+1 != self.n:
                s += "]\n"
        s += "]\n]"
        return s

    def __str__(self):
        return self.to_string()

    def zero_ixs(self):
        bag = set()
        for i in range(self.n):
            for j in range(self.m):
                if self._ref[i][j] == 0:
                    bag |= {(i, j)}
        return bag

    def zero(self):
        zs = m.zero_ixs()

        rows = {i for (i, _) in zs}
        cols = {j for (_, j) in zs}
        self._zero_rows_cols(rows, cols)

    def to_arr(self):
        return deepcopy(self._ref)

    def from_arr(self, arr):
        "Ensure the array is multidimensional, assigns to internal ref if so"
        def is_list(a):
            return type(a) == type([])
        if is_list(arr) and arr and is_list(arr[0]):
            self._ref = arr
            return True
        return False

    def _zero_rows_cols(self, rs, cs):
        for row in rs:
            for col in range(self.m):
                self.set(row, col, 0)
        for col in cs:
            for row in range(self.n):
                self.set(row, col, 0)


if __name__ == '__main__':
    cases = [
        ([[1, 0],
          [0, 1]],
         [[0, 0],
          [0, 0]]),
        ([[1, 1],
          [1, 1]],
         [[1, 1],
          [1, 1]]),
        ([[1, 1, 3],
          [1, 1, 0]],
         [[1, 1, 0],
          [0, 0, 0]]),
        ([[1, 1],
          [1, 1],
          [0, 1]],
         [[0, 1],
          [0, 1],
          [0, 0]]),
        ([[]],
         [[]]),
        ([[1]],
         [[1]]),
        ([[0]],
         [[0]])
    ]

    for inp, exp in cases:
        m = Matrix(inp)
        print('Before zeroing')
        print(m)
        print('')
        m.zero()
        print('After zeroing')
        print(m)
        print('')
        assert(m.to_arr() == exp)
