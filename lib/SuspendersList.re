open List;

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

let add = (xs, x) => [x, ...xs];

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

let partition = (xs, f) => {
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

let take = (xs, n) =>
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

let rec drop = (xs, n) =>
  if (n < 0) {
    None;
  } else if (n == 0) {
    Some(xs);
  } else {
    switch (xs) {
    | [_, ...t] => drop(t, n - 1)
    | [] => None
    };
  };

let splitAt = (xs, n) =>
  if (n < 0) {
    None;
  } else if (n == 0) {
    Some(([], xs));
  } else {
    switch (take(xs, n), drop(xs, n)) {
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

let zipBy = (xs, ys, f) => {
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
