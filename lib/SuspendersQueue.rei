module A = Suspenders__SuspendersArray;
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
let make: unit => t('a);
let clear: t('a) => unit;
let add: ('a, t('a)) => unit;
let peek: t('a) => option('a);
let peekExn: t('a) => 'a;
let pop: t('a) => option('a);
let popExn: t('a) => 'a;
let copy: t('a) => t('a);
let map: ('a => 'b, t('a)) => t('b);
let isEmpty: t('a) => bool;
let size: t('a) => int;
let forEach: ('a => 'b, t('a)) => unit;
let reduce: (('a, 'b) => 'a, 'a, t('b)) => 'a;
let transfer: (t('a), t('a)) => unit;
let toArray: t('a) => array('a);
let fromArray: array('a) => t('a);
