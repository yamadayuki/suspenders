type t('a) = {mutable root: option(cell('a))}
and cell('a) = {
  head: 'a,
  tail: option(cell('a)),
};
let make: unit => t('a);
let clear: t('a) => unit;
let copy: t('a) => t('a);
let push: ('a, t('a)) => unit;
let top: t('a) => option('a);
let isEmpty: t('a) => bool;
let pop: t('a) => option('a);
let size: t('a) => int;
let forEach: ('a => 'b, t('a)) => unit;
