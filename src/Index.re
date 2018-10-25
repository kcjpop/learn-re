let x: int = 2;

let rec even = x =>
  if (x <= 0) {
    true;
  } else {
    odd(x - 1);
  }
and odd = x =>
  if (x <= 0) {
    false;
  } else {
    even(x - 1);
  };

Js.log(odd(3));
Js.log(even(2));

let rec factorial = x =>
  if (x < 2) {
    x;
  } else {
    x * factorial(x - 1);
  };

let f = () => 123;
let addTuple = ((x: int, y: int)) => x + y;

{
  let add' = (~x, ~y) => x + y;
  let x = 8;
  let y = 7;
  Js.log(add'(~y, ~x));
};

{
  let add = (~x=?, ~y=?, ()): int =>
    switch (x, y) {
    | (Some(x'), Some(y')) => x' + y'
    | (Some(x'), None) => x'
    | (None, Some(y')) => y'
    | (None, None) => 0
    };

  Js.log(add(~x=4, ~y=3));
};

{
  /* Labelled function and fast pipe */
  let add = (~a, ~b) => a + b;
  let id = (~n) => n;

  /* Use _ place the position of fast pipe argument */
  id(~n=1)->add(~b=2, ~a=_);
};

/* Interface for Math' module */
module type MathInterface = {
  let add: (int, int) => int;
  let mul: (int, int) => int;
};

module Math': MathInterface = {
  let add = (x: int, y: int) => x + y;
  let mul = (x: int, y: int) => x * y;
};

{
  let xs = [1, 3, 4, 5];
  let result = List.map(x => x * 3, xs);
  Js.log(result);
  let result = List.map(Math'.mul(2), xs);
  Js.log(result);
};

{
  let double = (x: int) => x * 2;
  let repeat2 = (s: string) => s ++ s;
  let result = 4 |> double |> string_of_int |> repeat2;
  Js.log(result);
};

type tree('a) =
  | Empty
  | Node('a, tree('a), tree('a));

type expression =
  | Plus(expression, expression)
  | Minus(expression, expression)
  | Times(expression, expression)
  | DividedBy(expression, expression)
  | Literal(int);

{
  let rec eval = (e: expression) =>
    switch (e) {
    | Plus(e1, e2) => eval(e1) + eval(e2)
    | Minus(e1, e2) => eval(e1) - eval(e2)
    | Times(e1, e2) => eval(e1) * eval(e2)
    | DividedBy(e1, e2) => eval(e1) / eval(e2)
    | Literal(x) => x
    };
  /* (3 - (16 / (6 + 2)) */
  let expr =
    Minus(
      Literal(3),
      DividedBy(Literal(16), Plus(Literal(6), Literal(2))),
    );
  Js.log(eval(expr));
};

{
  /* A list */
  let xs = [1, 2];
  let ys = [3, 4, ...xs]; /* only spread at the end */
  let zs = xs @ ys; /* concat two lists, SLOW */

  let rec append' = (xs: list('a), ys: list('b)) =>
    switch (xs) {
    | [] => ys
    | [head, ...tail] => [head, ...append'(tail, ys)]
    };

  let rec getElementAt = (~index: int, xs: list('a)) =>
    switch (xs) {
    | [] => None
    | [head, ...tail] =>
      if (index <= 0) {
        Some(head);
      } else {
        getElementAt(~index=index - 1, tail);
      }
    };

  let rec getElementAt' = (~index: int, xs: list('a)) =>
    switch (xs) {
    | [] => None
    | [head, ..._] when index <= 0 => Some(head)
    | [_, ...tail] => getElementAt'(~index=index - 1, tail)
    };

  /* Print a list */
  Js.log(Array.of_list(zs));
  Js.log(append'([1, 2], [3, 4]));
  Js.log(getElementAt(~index=1, zs));
  Js.log(getElementAt'(~index=1, zs));
};

module Person = {
  type t = {
    firstName: string,
    lastName: string,
    email: string,
  };
  /* Record */
  let p = {firstName: "An", lastName: "Cao", email: ""};
  let pWithEmail = {...p, email: "an@ancaois.me"};
  let {firstName, _} = pWithEmail;
  Js.log(firstName);
};

module Plant = {
  type t = {name: string};
};

Js.log("Hello");
Js.log(Buckle.joe);