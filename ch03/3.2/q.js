const pop = ({ stack: [val, ...stack], mins: ms }) => {
  let mins = ms.length > 0 && ms[0] == val ? ms.splice(1) : ms;
  let rv = { val, stack, mins };
  return rv;
};

const push = ({ stack, val, mins: ms }) => {
  let mins;
  if (ms.length == 0) {
    mins = [val];
  } else {
    // Compare gteq as we need to always pop by equality. An alternative is
    // to compare by memory address and pop only when the exact object put on
    // is about to be popped.
    mins = ms.length > 0 && ms[0] >= val ? [val, ...ms] : ms;
  }
  let rv = { val: null, stack: [val, ...stack], mins };
  return rv;
};

const minPeek = ({ stack, val, mins }) => {
  if (mins.length > 0) {
    return mins[0];
  } else {
    return undefined;
  }
};

let s1 = pop(push({ stack: [], val: 12, mins: [] }));

// Wow this is so utterly unclear and confusing.
const examples = [
  minPeek(push({ ...push({ stack: [], mins: [], val: 1 }), val: 100 })) == 1,
  minPeek(push({ ...push({ stack: [], mins: [], val: 100 }), val: 1 })) == 1,
  minPeek(pop(push({ ...push({ stack: [], mins: [], val: 100 }), val: 1 }))) ==
    100,
  minPeek(
    pop(pop(push({ ...push({ stack: [], mins: [], val: 100 }), val: 1 })))
  ) == undefined,
  minPeek(
    pop(
      pop(
        pop(
          push({
            ...push({
              ...push({ ...push({ stack: [], mins: [], val: 5 }), val: 2 }),
              val: 3
            }),
            val: 2
          })
        )
      )
    )
  ) == 5
];

console.log(examples);
