let add: (int, int) => int = [%raw
  {|
  function(a, b) {
    console.log("hello from raw JavaScript!");
    return a + b
  }
|}
];

let f: (int, int) => int = [%raw (a, b) => "return a + b"];

let g = (a, b) => {
  [%debugger];
  a + b;
};

[@bs.val] external myFunction: int => string = "";
Js.log(myFunction(2));

type timerId;
[@bs.val] external setTimeout: (unit => unit, int) => timerId = "";
[@bs.val] external clearTimeout: timerId => unit = "";

let t = setTimeout(() => Js.log("what ever"), 2000);
clearTimeout(t);

Js.log(add(1, 2));

[@bs.scope "Math"] [@bs.val] external random: unit => float = "";
Js.log(random());

[@bs.scope ("window", "location", "history")] [@bs.val]
external push: string => unit = "";
push("/404");

[@bs.module "fs"] external readFile: string => string = "";
readFile("hello");

[@bs.module] external hasha: string => string = "";
hasha("hello");

[@bs.deriving abstract]
type person = {
  name: string,
  mutable age: int,
  job: string,
};

let joe = person(~name="Joe", ~job="dev", ~age=34);
let joeAge = ageGet(joe);
let joeJob = jobGet(joe);

joe->ageSet(21);

[@bs.val]
external draw: (~x: int, ~y: int, ~border: bool=?, unit) => unit = "";

draw(~x=1, ~y=2, ());

type document;
[@bs.send]
external getElementById: (document, string) => Dom.element = "getElementById";

[@bs.val] external doc: document = "";
let app = getElementById(doc, "js-app");

type readline;

[@bs.send]
external on:
  (
    readline,
    /* Use polymorphic variants */
    [@bs.string] [ | `close(unit => unit) | `line(string => unit)]
  ) =>
  readline =
  "";

let register = rl =>
  rl->on(`close(_e => ()))->on(`line(line => print_endline(line)));

external mstring: string => int = "%identity";
Js.log(mstring("hello"));