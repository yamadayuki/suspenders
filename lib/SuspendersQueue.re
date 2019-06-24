type t('a) = {
  mutable length: int,
  mutable first: cell('a),
  mutable last: cell('a),
}
and node('a) = {
  content: 'a,
  mutable next: cell('a),
}
and cell('a) = option(node('a));

let t = (~length, ~first, ~last) => {length, first, last};
let setLength = (v, q) => q.length = v;
let getLength = q => q.length;
let setFirst = (v, q) => q.first = v;
let getFirst = q => q.first;
let setLast = (v, q) => q.last = v;
let getLast = q => q.last;

let node = (~content, ~next) => {content, next};
let getContent = n => n.content;
let setNext = (v, n) => n.next = v;
let getNext = n => n.next;

let make = () => t(~length=0, ~first=None, ~last=None);

let clear = q => {
  setLength(0, q);
  setFirst(None, q);
  setLast(None, q);
};

let add = (x, q) => {
  let cell = Some(node(~content=x, ~next=None));
  switch (getLast(q)) {
  | None =>
    setLength(1, q);
    setFirst(cell, q);
    setLast(cell, q);
  | Some(last) =>
    setLength(getLength(q) + 1, q);
    setNext(cell, last);
    setLast(cell, q);
  };
};

let peek = q =>
  switch (getFirst(q)) {
  | None => None
  | Some(v) => Some(getContent(v))
  };

let peekExn = q =>
  switch (getFirst(q)) {
  | None => raise @@ invalid_arg("peekExn")
  | Some(v) => getContent(v)
  };

let pop = q =>
  switch (getFirst(q)) {
  | None => None
  | Some(x) =>
    let next = getNext(x);
    if (next == None) {
      clear(q);
      Some(getContent(x));
    } else {
      setLength(getLength(q) - 1, q);
      setFirst(next, q);
      Some(getContent(x));
    };
  };

let popExn = q =>
  switch (getFirst(q)) {
  | None => failwith("Empty")
  | Some(x) =>
    let next = getNext(x);
    if (next == None) {
      clear(q);
      getContent(x);
    } else {
      setLength(getLength(q) - 1, q);
      setFirst(next, q);
      getContent(x);
    };
  };

let rec copyAux = (prev, cell, q) => {
  switch (cell) {
  | None =>
    setLast(prev, q);
    q;
  | Some(x) =>
    let content = getContent(x);
    let res = Some(node(~content, ~next=None));
    switch (prev) {
    | None => setFirst(res, q)
    | Some(p) => setNext(res, p)
    };
    copyAux(res, getNext(x), q);
  };
};

let copy = q =>
  copyAux(
    None,
    getFirst(q),
    t(~length=getLength(q), ~first=None, ~last=None),
  );
