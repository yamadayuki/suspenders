type t('a) = {mutable root: option(cell('a))}
and cell('a) = {
  head: 'a,
  tail: option(cell('a)),
};

let t = (~root) => {root: root};
let setRoot = (v, s) => s.root = v;
let getRoot = s => s.root;

let cell = (~head, ~tail) => {head, tail};
let getHead = c => c.head;
let getTail = c => c.tail;

let make = () => t(~root=None);

let clear = s => setRoot(None, s);

let copy = s => t(~root=s.root);

let push = (x, s) => setRoot(Some(cell(~head=x, ~tail=getRoot(s))), s);

let top = s =>
  switch (getRoot(s)) {
  | Some(x) => Some(getHead(x))
  | None => None
  };

let isEmpty = s => getRoot(s) == None;

let pop = s =>
  switch (getRoot(s)) {
  | Some(x) =>
    setRoot(getTail(x), s);
    Some(getHead(x));
  | None => None
  };

let rec sizeAux = (acc, s) =>
  switch (getTail(s)) {
  | None => acc + 1
  | Some(x) => sizeAux(acc + 1, x)
  };

let size = s =>
  switch (getRoot(s)) {
  | None => 0
  | Some(x) => sizeAux(0, x)
  };

let rec forEachAux = (f, s: option(cell(_))) =>
  switch (s) {
  | Some(x) =>
    f(getHead(x));
    forEachAux(f, getTail(x));
  | None => ()
  };

let forEach = (f, s) => forEachAux(f, getRoot(s));
