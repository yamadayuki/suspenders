include Array;

let getExn = (xs, i) => xs[i];
let setExn = (xs, i, v) => xs[i] = v;

let swapExn = (xs, i, j) => {
  let tmp = getExn(xs, i);
  setExn(xs, i, getExn(xs, j));
  setExn(xs, j, tmp);
};

let shuffleInPlace = xs => {
  Random.self_init();
  let len = length(xs);
  for (i in 0 to len - 1) {
    swapExn(xs, i, Random.int(len));
  };
};

let shuffle = xs => {
  let result = copy(xs);
  shuffleInPlace(result);
  result;
};

let reverseInPlace = xs => {
  let len = length(xs);
  for (i in 0 to len / 2 - 1) {
    swapExn(xs, i, len - i - 1);
  };
};

let reverse = xs => {
  let result = copy(xs);
  reverseInPlace(result);
  result;
};

let makeBy = (l, f) => {
  let result = make(l, f(0));
  for (i in 1 to l - 1) {
    setExn(result, i, f(i));
  };
  result;
};

let makeByAndShuffle = (l, f) => {
  let result = makeBy(l, f);
  shuffleInPlace(result);
  result;
};

let range = (start, finish) => {
  let count = finish - start + 1;
  if (count < 0) {
    [||];
  } else {
    let result = make(count, 0);
    for (i in 0 to count - 1) {
      setExn(result, i, start + i);
    };
    result;
  };
};

let rangeBy = (~step, start, finish) => {
  let cut = finish - start;
  if (cut < 0 || step <= 0) {
    [||];
  } else {
    let count = cut / step + 1;
    let result = make(count, 0);
    let curr = ref(start);
    for (i in 0 to count - 1) {
      setExn(result, i, curr^);
      curr := curr^ + step;
    };

    result;
  };
};

let zip = (xs, ys) => {
  let (lenx, leny) = (length(xs), length(ys));
  let len = min(lenx, leny);
  let result = make(len, (getExn(xs, 0), getExn(ys, 0)));
  for (i in 0 to len - 1) {
    setExn(result, i, (getExn(xs, i), getExn(ys, i)));
  };
  result;
};

let zipBy = (f, xs, ys) => {
  let (lenx, leny) = (length(xs), length(ys));
  let len = min(lenx, leny);
  let result = make(len, f(getExn(xs, 0), getExn(ys, 0)));
  for (i in 0 to len - 1) {
    setExn(result, i, f(getExn(xs, i), getExn(ys, i)));
  };
  result;
};

let concatMany = arrs => {
  let lenArrs = length(arrs);
  let totalLen = ref(0);
  for (i in 0 to lenArrs - 1) {
    totalLen := totalLen^ + length(getExn(arrs, i));
  };
  let result = make(totalLen^, getExn(getExn(arrs, 0), 0));
  totalLen := 0;
  for (j in 0 to lenArrs - 1) {
    let curr = getExn(arrs, j);
    for (k in 0 to length(curr) - 1) {
      setExn(result, totalLen^, getExn(curr, k));
      incr(totalLen);
    };
  };
  result;
};

let slice = (offset, len, xs) =>
  if (len <= 0) {
    [||];
  } else {
    let l = length(xs);
    let ofs =
      if (offset < 0) {
        max(l + offset, 0);
      } else {
        offset;
      };
    let hasLen = l - ofs;
    let copyLength = min(hasLen, len);
    if (copyLength <= 0) {
      [||];
    } else {
      let result = make(copyLength, getExn(xs, 0));
      for (i in 0 to copyLength - 1) {
        setExn(result, i, getExn(xs, ofs + i));
      };
      result;
    };
  };

let sliceToEnd = (offset, xs) => {
  let lenxs = length(xs);
  let ofs =
    if (offset < 0) {
      max(lenxs + offset, 0);
    } else {
      offset;
    };
  let len = lenxs - ofs;
  let result = make(len, getExn(xs, 0));
  for (i in 0 to len - 1) {
    setExn(result, i, getExn(xs, ofs + i));
  };
  result;
};

let fill = (offset, len, v, xs) =>
  if (len > 0) {
    let len = length(xs);
    let ofs = offset < 0 ? max(len + offset, 0) : offset;
    let fillLength = min(len - ofs, len);
    if (fillLength > 0) {
      for (i in ofs to ofs + fillLength - 1) {
        setExn(xs, i, v);
      };
    };
  };

let forEach = (f, xs) =>
  for (i in 0 to length(xs) - 1) {
    f(getExn(xs, i));
  };

let forEachi = (f, xs) =>
  for (i in 0 to length(xs) - 1) {
    f(i, getExn(xs, i));
  };

let getBy = (f, xs) => {
  let l = length(xs);
  let i = ref(0);
  let r = ref(None);

  while (r^ == None && i^ < l) {
    let v = getExn(xs, i^);
    if (f(v)) {
      r := Some(v);
    };
    incr(i);
  };

  r^;
};

let getIndexBy = (f, xs) => {
  let l = length(xs);
  let i = ref(0);
  let r = ref(None);

  while (r^ == None && i^ < l) {
    let v = getExn(xs, i^);
    if (f(v)) {
      r := Some(i^);
    };
    incr(i);
  };

  r^;
};

let keep = (f, xs) => {
  let l = length(xs);
  let result = make(l, getExn(xs, 0));
  let j = ref(0);
  for (i in 0 to l - 1) {
    let v = getExn(xs, i);
    if (f(v)) {
      setExn(result, j^, v);
      incr(j);
    };
  };
  slice(0, j^, result);
};

let keepi = (f, xs) => {
  let l = length(xs);
  let result = make(l, getExn(xs, 0));
  let j = ref(0);
  for (i in 0 to l - 1) {
    let v = getExn(xs, i);
    if (f(i, v)) {
      setExn(result, j^, v);
      incr(j);
    };
  };
  slice(0, j^, result);
};

let keepMap = (f, xs) => {
  let l = length(xs);
  let result = make(l, getExn(xs, 0));
  let j = ref(0);
  for (i in 0 to l - 1) {
    let v = getExn(xs, i);
    switch (f(v)) {
    | None => ()
    | Some(v) =>
      setExn(result, j^, v);
      incr(j);
    };
  };
  slice(0, j^, result);
};

let reduce = (f, acc, xs) => {
  let result = ref(acc);
  for (i in 0 to length(xs) - 1) {
    result := f(result^, getExn(xs, i));
  };
  result^;
};

let reduceReverse = (f, acc, xs) => {
  let result = ref(acc);
  for (i in length(xs) - 1 downto 0) {
    result := f(result^, getExn(xs, i));
  };
  result^;
};

let reducei = (f, acc, xs) => {
  let result = ref(acc);
  for (i in 0 to length(xs) - 1) {
    result := f(i, result^, getExn(xs, i));
  };
  result^;
};

let reduceReversei = (f, acc, xs) => {
  let result = ref(acc);
  for (i in length(xs) - 1 downto 0) {
    result := f(i, result^, getExn(xs, i));
  };
  result^;
};

let rec everyAux = (xs, i, f, len) =>
  if (i == len) {
    true;
  } else if (f @@ getExn(xs, i)) {
    everyAux(xs, i + 1, f, len);
  } else {
    false;
  };

let every = (f, xs) => {
  let len = length(xs);
  everyAux(xs, 0, f, len);
};

let rec someAux = (xs, i, f, len) =>
  if (i == len) {
    false;
  } else if (f @@ getExn(xs, i)) {
    true;
  } else {
    someAux(xs, i + 1, f, len);
  };

let some = (f, xs) => {
  let len = length(xs);
  someAux(xs, 0, f, len);
};

let rec eqAux = (xs, ys, i, f, len) =>
  if (i == len) {
    true;
  } else if (f(getExn(xs, i), getExn(ys, i))) {
    eqAux(xs, ys, i + 1, f, len);
  } else {
    false;
  };

let eq = (f, xs, ys) => {
  let lenxs = length(xs);
  let lenys = length(ys);
  if (lenxs == lenys) {
    eqAux(xs, ys, 0, f, lenxs);
  } else {
    false;
  };
};

let rec cmpAux = (xs, ys, i, f, len) =>
  if (i == len) {
    0;
  } else {
    let c = f(getExn(xs, i), getExn(ys, i));
    if (c == 0) {
      cmpAux(xs, ys, i + 1, f, len);
    } else {
      c;
    };
  };

let cmp = (f, xs, ys) => {
  let lenxs = length(xs);
  let lenys = length(ys);
  if (lenxs > lenys) {
    1;
  } else if (lenxs < lenys) {
    (-1);
  } else {
    cmpAux(xs, ys, 0, f, lenxs);
  };
};

let partition = (f, xs) => {
  let l = length(xs);
  let i = ref(0);
  let j = ref(0);
  let a1 = make(l, getExn(xs, 0));
  let a2 = make(l, getExn(xs, 0));
  for (ii in 0 to l - 1) {
    let v = getExn(xs, ii);
    if (f(. v)) {
      setExn(a1, i^, v);
      incr(i);
    } else {
      setExn(a2, j^, v);
      incr(j);
    };
  };
  (slice(0, i^, a1), slice(0, j^, a2));
};

let unzip = arr => {
  let l = length(arr);
  let (x, y) = getExn(arr, 0);
  let xs = make(l, x);
  let ys = make(l, y);
  for (i in 0 to l - 1) {
    let (v1, v2) = getExn(arr, i);
    setExn(xs, i, v1);
    setExn(ys, i, v2);
  };
  (xs, ys);
};
