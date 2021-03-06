external length: array('a) => int = "%array_length";
external get: (array('a), int) => 'a = "%array_safe_get";
external set: (array('a), int, 'a) => unit = "%array_safe_set";
external make: (int, 'a) => array('a) = "caml_make_vect";
external create: (int, 'a) => array('a) = "caml_make_vect";
external create_float: int => array(float) = "caml_make_float_vect";
let make_float: int => array(float);
let init: (int, int => 'a) => array('a);
let make_matrix: (int, int, 'a) => array(array('a));
let create_matrix: (int, int, 'a) => array(array('a));
let append: (array('a), array('a)) => array('a);
let concat: list(array('a)) => array('a);
let sub: (array('a), int, int) => array('a);
let copy: array('a) => array('a);
let blit: (array('a), int, array('a), int, int) => unit;
let to_list: array('a) => list('a);
let of_list: list('a) => array('a);
let iter: ('a => unit, array('a)) => unit;
let iteri: ((int, 'a) => unit, array('a)) => unit;
let map: ('a => 'b, array('a)) => array('b);
let mapi: ((int, 'a) => 'b, array('a)) => array('b);
let fold_left: (('a, 'b) => 'a, 'a, array('b)) => 'a;
let fold_right: (('b, 'a) => 'a, array('b), 'a) => 'a;
let iter2: (('a, 'b) => unit, array('a), array('b)) => unit;
let map2: (('a, 'b) => 'c, array('a), array('b)) => array('c);
let for_all: ('a => bool, array('a)) => bool;
let exists: ('a => bool, array('a)) => bool;
let mem: ('a, array('a)) => bool;
let memq: ('a, array('a)) => bool;
let sort: (('a, 'a) => int, array('a)) => unit;
let stable_sort: (('a, 'a) => int, array('a)) => unit;
let fast_sort: (('a, 'a) => int, array('a)) => unit;
external unsafe_get: (array('a), int) => 'a = "%array_unsafe_get";
external unsafe_set: (array('a), int, 'a) => unit = "%array_unsafe_set";
module Floatarray = Array.Floatarray;

// From SuspendersArray

// Getter and setter
let getExn: (array('a), int) => 'a;
let setExn: (array('a), int, 'a) => unit;
let getBy: ('a => bool, array('a)) => option('a);
let getByi: ('a => bool, array('a)) => option(int);

// Manipulation
let swapExn: (array('a), int, int) => unit;
let shuffleInPlace: array('a) => unit;
let shuffle: array('a) => array('a);
let reverseInPlace: array('a) => unit;
let reverse: array('a) => array('a);
let slice: (int, int, array('a)) => array('a);
let sliceToEnd: (int, array('a)) => array('a);
let concatMany: array(array('a)) => array('a);
let fillInPlace: (int, int, 'a, array('a)) => unit;
let fill: (int, int, 'a, array('a)) => array('a);
let keep: ('a => bool, array('a)) => array('a);
let keepi: ((int, 'a) => bool, array('a)) => array('a);
let keepMap: ('a => option('a), array('a)) => array('a);
let unique: array('a) => array('a);

// Initialization
let makeBy: (int, int => 'a) => array('a);
let makeByAndShuffle: (int, int => 'a) => array('a);
let range: (int, int) => array(int);
let rangeBy: (~step: int, int, int) => array(int);

// Iterator
let forEach: ('a => unit, array('a)) => unit;
let forEachi: ((int, 'a) => unit, array('a)) => unit;
let reduce: (('b, 'a) => 'b, 'b, array('a)) => 'b;
let reduceReverse: (('b, 'a) => 'b, 'b, array('a)) => 'b;
let reducei: ((int, 'b, 'a) => 'b, 'b, array('a)) => 'b;
let reduceReversei: ((int, 'b, 'a) => 'b, 'b, array('a)) => 'b;

// Scanning
let every: ('a => bool, array('a)) => bool;
let some: ('a => bool, array('a)) => bool;
let eq: (('a, 'b) => bool, array('a), array('b)) => bool;
let cmp: (('a, 'b) => int, array('a), array('b)) => int;

// Arrays of pairs
let zip: (array('a), array('b)) => array(('a, 'b));
let zipBy: (('a, 'b) => 'c, array('a), array('b)) => array('c);
let unzip: array(('a, 'b)) => (array('a), array('b));
let partition: ('a => bool, array('a)) => (array('a), array('a));
