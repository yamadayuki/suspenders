let mapWithDefault: ('b, 'a => 'b, option('a)) => 'b;
let map: ('a => 'b, option('a)) => option('b);
let flatMap: ('a => option('b), option('a)) => option('b);
let getWithDefault: ('a, option('a)) => 'a;
let isSome: option('a) => bool;
let isNone: option('a) => bool;
let eq: (('a, 'b) => bool, option('a), option('b)) => bool;
let cmp: (('a, 'b) => int, option('a), option('b)) => int;
