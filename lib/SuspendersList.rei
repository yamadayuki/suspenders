let length: list('a) => int;
let compare_lengths: (list('a), list('b)) => int;
let compare_length_with: (list('a), int) => int;
let cons: ('a, list('a)) => list('a);
let hd: list('a) => 'a;
let tl: list('a) => list('a);
let nth: (list('a), int) => 'a;
let nth_opt: (list('a), int) => option('a);
let rev: list('a) => list('a);
let init: (int, int => 'a) => list('a);
let append: (list('a), list('a)) => list('a);
let rev_append: (list('a), list('a)) => list('a);
let concat: list(list('a)) => list('a);
let flatten: list(list('a)) => list('a);
let iter: ('a => unit, list('a)) => unit;
let iteri: ((int, 'a) => unit, list('a)) => unit;
let map: ('a => 'b, list('a)) => list('b);
let mapi: ((int, 'a) => 'b, list('a)) => list('b);
let rev_map: ('a => 'b, list('a)) => list('b);
let fold_left: (('a, 'b) => 'a, 'a, list('b)) => 'a;
let fold_right: (('a, 'b) => 'b, list('a), 'b) => 'b;
let iter2: (('a, 'b) => unit, list('a), list('b)) => unit;
let map2: (('a, 'b) => 'c, list('a), list('b)) => list('c);
let rev_map2: (('a, 'b) => 'c, list('a), list('b)) => list('c);
let fold_left2: (('a, 'b, 'c) => 'a, 'a, list('b), list('c)) => 'a;
let fold_right2: (('a, 'b, 'c) => 'c, list('a), list('b), 'c) => 'c;
let for_all: ('a => bool, list('a)) => bool;
let exists: ('a => bool, list('a)) => bool;
let for_all2: (('a, 'b) => bool, list('a), list('b)) => bool;
let exists2: (('a, 'b) => bool, list('a), list('b)) => bool;
let mem: ('a, list('a)) => bool;
let memq: ('a, list('a)) => bool;
let find: ('a => bool, list('a)) => 'a;
let find_opt: ('a => bool, list('a)) => option('a);
let filter: ('a => bool, list('a)) => list('a);
let find_all: ('a => bool, list('a)) => list('a);
let assoc: ('a, list(('a, 'b))) => 'b;
let assoc_opt: ('a, list(('a, 'b))) => option('b);
let assq: ('a, list(('a, 'b))) => 'b;
let assq_opt: ('a, list(('a, 'b))) => option('b);
let mem_assoc: ('a, list(('a, 'b))) => bool;
let mem_assq: ('a, list(('a, 'b))) => bool;
let remove_assoc: ('a, list(('a, 'b))) => list(('a, 'b));
let remove_assq: ('a, list(('a, 'b))) => list(('a, 'b));
let split: list(('a, 'b)) => (list('a), list('b));
let combine: (list('a), list('b)) => list(('a, 'b));
let sort: (('a, 'a) => int, list('a)) => list('a);
let stable_sort: (('a, 'a) => int, list('a)) => list('a);
let fast_sort: (('a, 'a) => int, list('a)) => list('a);
let sort_uniq: (('a, 'a) => int, list('a)) => list('a);
let merge: (('a, 'a) => int, list('a), list('a)) => list('a);

// From SuspendersList

// Getter and setter
let head: list('a) => option('a);
let headExn: list('a) => 'a;
let tail: list('a) => option(list('a));
let tailExn: list('a) => list('a);
let get: (list('a), int) => option('a);
let getExn: (list('a), int) => 'a;
let add: ('a, list('a)) => list('a);

// Transformation
let fromArray: array('a) => list('a);
let toArray: list('a) => array('a);

// Manipulation
let take: (int, list('a)) => option(list('a));
let drop: (int, list('a)) => option(list('a));
let splitAt: (int, list('a)) => option((list('a), list('a)));
let shuffle: list('a) => list('a);
let unique: list('a) => list('a);
let reverse: list('a) => list('a);
let keep: ('a => bool, list('a)) => list('a);
let keepi: ((int, 'a) => bool, list('a)) => list('a);
let keepMap: ('a => option('a), list('a)) => list('a);
let slice: (int, int, list('a)) => list('a);
let sliceToEnd: (int, list('a)) => list('a);
let swapExn: (list('a), int, int) => list('a);

// Initialization
let makeBy: (int, int => 'a) => list('a);
let make: (int, 'a) => list('a);
let range: (int, int) => list(int);
let rangeBy: (~step: int, int, int) => list(int);

// Iterator
let forEach: ('a => unit, list('a)) => unit;
let forEachi: ((int, 'a) => unit, list('a)) => unit;
let reduce: (('a, 'b) => 'a, 'a, list('b)) => 'a;
let reduceReverse: (('a, 'b) => 'a, 'a, list('b)) => 'a;
let reducei: ((int, 'a, 'b) => 'a, 'a, list('b)) => 'a;
let reduceReversei: ((int, 'a, 'b) => 'a, 'a, list('b)) => 'a;
let mapReverse: ('a => 'b, list('a)) => list('b);

// Scanning
let every: ('a => bool, list('a)) => bool;
let some: ('a => bool, list('a)) => bool;
let eq: (('a, 'b) => bool, list('a), list('b)) => bool;
let cmp: (('a, 'b) => int, list('a), list('b)) => int;

// Lists of pairs
let zip: (list('a), list('b)) => list(('a, 'b));
let zipBy: (('a, 'b) => 'c, list('a), list('b)) => list('c);
let unzip: list(('a, 'b)) => (list('a), list('b));
let partition: ('a => bool, list('a)) => (list('a), list('a));
