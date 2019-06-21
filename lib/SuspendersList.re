include List;

module A = Suspenders__SuspendersArray;

/**
 * Getter and setter
 */

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

let add = (x, xs) => [x, ...xs];

/**
 * Transformation
 */

let fromArray = xs => {
  let len = A.length(xs);
  if (len <= 0) {
    [];
  } else {
    let result = ref([]);
    for (i in 0 to len - 1) {
      result := result^ @ [A.getExn(xs, i)];
    };
    result^;
  };
};

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

/**
 * Manipuration
 */

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

let shuffle = xs => {
  let arr = toArray(xs);
  A.shuffleInPlace(arr);
  fromArray(arr);
};

let unique = xs => {
  let result = ref([]);

  for (i in 0 to length(xs) - 1) {
    let item = getExn(xs, i);
    if (!mem(item, result^)) {
      result := result^ @ [item];
    };
  };

  result^;
};

let reverse = rev;

let rec keepAux = (f, acc, xs) =>
  switch (xs) {
  | [] => acc
  | [h, ...t] =>
    if (f(h)) {
      keepAux(f, acc @ [h], t);
    } else {
      keepAux(f, acc, t);
    }
  };

let keep = (f, xs) => keepAux(f, [], xs);

let rec keepiAux = (f, i, acc, xs) =>
  switch (xs) {
  | [] => acc
  | [h, ...t] =>
    if (f(i, h)) {
      keepiAux(f, i + 1, acc @ [h], t);
    } else {
      keepiAux(f, i + 1, acc, t);
    }
  };

let keepi = (f, xs) => keepiAux(f, 0, [], xs);

let rec keepMapAux = (f, acc, xs) =>
  switch (xs) {
  | [] => acc
  | [h, ...t] =>
    switch (f(h)) {
    | None => keepMapAux(f, acc, t)
    | Some(v) => keepMapAux(f, acc @ [v], t)
    }
  };

let keepMap = (f, xs) => keepMapAux(f, [], xs);

/**
 * Initialization
 */

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

let range = (start, finish) => {
  let count = finish - start + 1;
  if (count < 0) {
    [];
  } else {
    let result = ref([]);
    for (i in 0 to count - 1) {
      result := result^ @ [start + i];
    };
    result^;
  };
};

let rangeBy = (~step, start, finish) => {
  let cut = finish - start;
  if (cut < 0 || step <= 0) {
    [];
  } else {
    let count = cut / step + 1;
    let result = ref([]);
    let curr = ref(start);
    for (i in 0 to count - 1) {
      result := result^ @ [curr^];
      curr := curr^ + step;
    };
    result^;
  };
};

/**
 * Iterrator
 */

let rec forEach = (f, xs) => {
  switch (xs) {
  | [] => ()
  | [h, ...t] =>
    f(h);
    forEach(f, t);
  };
};

let rec forEachiAux = (f, i, xs) => {
  switch (xs) {
  | [] => ()
  | [h, ...t] =>
    f(i, h);
    forEachiAux(f, i + 1, t);
  };
};

let forEachi = (f, xs) => forEachiAux(f, 0, xs);

let rec reduce = (f, acc, xs) => xs |> toArray |> A.reduce(f, acc);

let rec reduceReverse = (f, acc, xs) =>
  xs |> toArray |> A.reduceReverse(f, acc);

let rec reducei = (f, acc, xs) => xs |> toArray |> A.reducei(f, acc);

let rec reduceReversei = (f, acc, xs) =>
  xs |> toArray |> A.reduceReversei(f, acc);

let rec mapReverseAux = (f, acc, xs) =>
  switch (xs) {
  | [] => acc
  | [h, ...t] => mapReverseAux(f, [f(h), ...acc], t)
  };

let mapReverse = (f, xs) => mapReverseAux(f, [], xs);

/**
 * Scanning
 */

let rec every = (f, xs) =>
  switch (xs) {
  | [] => true
  | [h, ...t] => f(h) && every(f, t)
  };

let rec some = (f, xs) =>
  switch (xs) {
  | [] => false
  | [h, ...t] => f(h) || some(f, t)
  };

let rec eq = (f, xs, ys) => {
  switch (xs, ys) {
  | ([], []) => true
  | ([], _)
  | (_, []) => false
  | ([xh, ...xt], [yh, ...yt]) =>
    if (f(xh, yh)) {
      eq(f, xt, yt);
    } else {
      false;
    }
  };
};

let rec cmp = (f, xs, ys) => {
  switch (xs, ys) {
  | ([], []) => 0
  | ([], _) => (-1)
  | (_, []) => 1
  | ([xh, ...xt], [yh, ...yt]) =>
    let cond = f(xh, yh);
    if (cond == 0) {
      cmp(f, xt, yt);
    } else {
      cond;
    };
  };
};

/**
 * Lists of pairs
 */

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

let unzip = xs => {
  fold_left(((ys, zs), (y, z)) => (ys @ [y], zs @ [z]), ([], []), xs);
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
