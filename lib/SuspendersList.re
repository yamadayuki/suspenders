open List;

module A = Suspenders__SuspendersArray;

let head =
  fun
  | [] => None
  | [x, ..._] => Some(x);

let headExn =
  fun
  | [] => raise @@ invalid_arg("headExn")
  | [x, ..._] => x;

let tail =
  fun
  | [] => None
  | [_, ...xs] => Some(xs);

let tailExn =
  fun
  | [] => raise @@ invalid_arg("tailExn")
  | [_, ...xs] => xs;

let fromArray = A.to_list;

let rec toArrayAux = (xs, i, x) => {
  switch (x) {
  | [] => xs
  | [h, ...t] =>
    A.setExn(xs, i, h);
    toArrayAux(xs, i + 1, t);
  };
};

let toArray = xs => {
  let len = length(xs);
  if (len <= 0) {
    [||];
  } else {
    let arr = A.make(len, headExn(xs));
    toArrayAux(arr, 0, xs);
  };
};

let add = (x, xs) => [x, ...xs];

let rec get = (xs, n) =>
  switch (xs) {
  | [h, ..._] when n == 0 => Some(h)
  | [_, ...t] when n > 0 => get(t, n - 1)
  | _ => None
  };

let rec getExn = (xs, n) =>
  switch (xs) {
  | [h, ..._] when n == 0 => h
  | [_, ...t] when n > 0 => getExn(t, n - 1)
  | _ => raise @@ invalid_arg("getExn")
  };

let partition = (f, xs) => {
  fold_left(
    ((ys, zs), x) =>
      if (f(x)) {
        (ys @ [x], zs);
      } else {
        (ys, zs @ [x]);
      },
    ([], []),
    xs,
  );
};

let unzip = xs => {
  fold_left(((ys, zs), (y, z)) => (ys @ [y], zs @ [z]), ([], []), xs);
};

let rec zipAux = (xs, ys, prec) => {
  switch (xs, ys) {
  | ([xh, ...xt], [yh, ...yt]) => zipAux(xt, yt, prec @ [(xh, yh)])
  | ([], _)
  | (_, []) => prec
  };
};

let zip = (xs, ys) =>
  switch (xs, ys) {
  | ([], _)
  | (_, []) => []
  | (x, y) => zipAux(x, y, [])
  };

let rec takeAux = (n, cell, prec) =>
  if (n == 0) {
    prec;
  } else {
    switch (cell) {
    | [] => []
    | [x, ...xs] => takeAux(n - 1, xs, prec @ [x])
    };
  };

let take = (n, xs) =>
  if (n < 0) {
    None;
  } else if (n == 0) {
    Some([]);
  } else {
    switch (xs) {
    | [] => None
    | [h, ...t] =>
      let has = takeAux(n - 1, t, [h]);
      length(has) > 0 ? Some(has) : None;
    };
  };

let rec drop = (n, xs) =>
  if (n < 0) {
    None;
  } else if (n == 0) {
    Some(xs);
  } else {
    switch (xs) {
    | [_, ...t] => drop(n - 1, t)
    | [] => None
    };
  };

let splitAt = (n, xs) =>
  if (n < 0) {
    None;
  } else if (n == 0) {
    Some(([], xs));
  } else {
    switch (take(n, xs), drop(n, xs)) {
    | (Some(l), Some(r)) => Some((l, r))
    | (None, Some(r)) => Some(([], r))
    | _ => None
    };
  };

let rec zipByAux = (f, xs, ys, prec) => {
  switch (xs, ys) {
  | ([xh, ...xt], [yh, ...yt]) => zipByAux(f, xt, yt, prec @ [f(xh, yh)])
  | ([], _)
  | (_, []) => prec
  };
};

let zipBy = (f, xs, ys) => {
  switch (xs, ys) {
  | ([], _)
  | (_, []) => []
  | (x, y) => zipByAux(f, x, y, [])
  };
};

let makeBy = (n, f) =>
  if (n <= 0) {
    [];
  } else {
    let cur = ref([f(0)]);
    let i = ref(1);
    while (i^ < n) {
      let v = [f(i^)];
      cur := cur^ @ v;
      incr(i);
    };
    cur^;
  };

let make = (n, v) =>
  if (n <= 0) {
    [];
  } else {
    let cur = ref([v]);
    let i = ref(1);
    while (i^ < n) {
      cur := cur^ @ [v];
      incr(i);
    };
    cur^;
  };

let shuffle = xs => {
  let arr = toArray(xs);
  A.shuffleInPlace(arr);
  fromArray(arr);
};

let reverse = rev;

let rec mapReverseAux = (f, acc, xs) =>
  switch (xs) {
  | [] => acc
  | [h, ...t] => mapReverseAux(f, [f(h), ...acc], t)
  };

let mapReverse = (f, xs) => mapReverseAux(f, [], xs);

let forEach = iter;
let forEachi = iteri;

let rec reduce = (f, acc, xs) => xs |> toArray |> A.reduce(f, acc);

let rec reduceReverse = (f, acc, xs) =>
  xs |> toArray |> A.reduceReverse(f, acc);

let rec reducei = (f, acc, xs) => xs |> toArray |> A.reducei(f, acc);