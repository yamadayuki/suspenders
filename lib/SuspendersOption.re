let mapWithDefault = (opt, default, f) =>
  switch (opt) {
  | Some(x) => f(x)
  | None => default
  };

let map = (opt, f) =>
  switch (opt) {
  | Some(x) => Some(f(x))
  | None => None
  };

let flatMap = (opt, f) =>
  switch (opt) {
  | Some(x) => f(x)
  | None => None
  };

let getWithDefault = (opt, default) =>
  switch (opt) {
  | Some(x) => x
  | None => default
  };

let isSome =
  fun
  | Some(_) => true
  | None => false;

let isNone = x => x == None;

let eq = (a, b, f) =>
  switch (a) {
  | Some(a) =>
    switch (b) {
    | None => false
    | Some(b) => f(a, b)
    }
  | None => b == None
  };

let cmp = (a, b, f) =>
  switch (a, b) {
  | (Some(a), Some(b)) => f(a, b)
  | (None, Some(_)) => (-1)
  | (Some(_), None) => 1
  | (None, None) => 0
  };
