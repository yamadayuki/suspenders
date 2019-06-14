let mapWithDefault: (option('a), 'b, 'a => 'b) => 'b;
let map: (option('a), 'a => 'b) => option('b);
let flatMap: (option('a), 'a => option('b)) => option('b);
let getWithDefault: (option('a), 'a) => 'a;
let isSome: option('a) => bool;
let isNone: option('a) => bool;
let eq: (option('a), option('b), ('a, 'b) => bool) => bool;
let cmp: (option('a), option('b), ('a, 'b) => int) => int;
