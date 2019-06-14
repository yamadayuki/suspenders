open TestFramework;
open Suspenders.List;

describe("List", ({describe, test}) => {
  test("head", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => head(list)).not.toThrow();
    expect.option(head(list)).toBe(Some(1));
  });

  describe("headExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => headExn(list)).not.toThrow();
      expect.int(headExn(list)).toBe(1);
    });

    test("throws", ({expect}) => {
      let list = [];
      expect.fn(() => headExn(list)).toThrow();
    });
  });

  test("tail", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => tail(list)).not.toThrow();
    expect.option(tail(list)).toBe(Some([2, 3]));
  });

  describe("tailExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => tailExn(list)).not.toThrow();
      expect.list(tailExn(list)).toEqual([2, 3]);
    });

    test("throws", ({expect}) => {
      let list = [];
      expect.fn(() => tailExn(list)).toThrow();
    });
  });

  test("add", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => add(list, 0)).not.toThrow();
    expect.list(add(list, 0)).toEqual([0, 1, 2, 3]);
  });

  test("get", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => get(list, 0)).not.toThrow();
    expect.option(get(list, 0)).toBe(Some(1));
    expect.option(get(list, 5)).toBe(None);
  });

  describe("getExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => getExn(list, 0)).not.toThrow();
      expect.int(getExn(list, 0)).toBe(1);
    });

    test("throws", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => getExn(list, 5)).toThrow();
    });
  });

  test("partition", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => partition(list, x => true)).not.toThrow();
    expect.equal(partition(list, x => x mod 2 == 1), ([1, 3], [2]));
  });

  test("unzip", ({expect}) => {
    let list = [(1, 2), (2, 3), (3, 4)];
    expect.fn(() => unzip(list)).not.toThrow();
    expect.equal(unzip(list), ([1, 2, 3], [2, 3, 4]));
  });

  test("zip", ({expect}) => {
    let xs = [1, 2, 3];
    let ys = [4, 5, 6, 7];
    expect.fn(() => zip(xs, ys)).not.toThrow();
    expect.equal(zip(xs, ys), [(1, 4), (2, 5), (3, 6)]);
  });

  test("take", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => take(list, 2)).not.toThrow();
    expect.option(take(list, 2)).toBe(Some([1, 2]));
  });

  test("drop", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => drop(list, 2)).not.toThrow();
    expect.option(drop(list, 2)).toBe(Some([3]));
  });

  test("splitAt", ({expect}) => {
    let list = [1, 2, 3];
    expect.fn(() => splitAt(list, 2)).not.toThrow();
    expect.option(splitAt(list, 2)).toBe(Some(([1, 2], [3])));
  });

  test("zipBy", ({expect}) => {
    let xs = [1, 2, 3];
    let ys = [4, 5, 6, 7];
    expect.fn(() => zipBy(xs, ys, (x, y) => x + y)).not.toThrow();
    expect.list(zipBy(xs, ys, (x, y) => x + y)).toEqual([5, 7, 9]);
  });

  test("makeBy", ({expect}) => {
    expect.fn(() => makeBy(3, x => x * x)).not.toThrow();
    expect.list(makeBy(3, x => x * x)).toEqual([0, 1, 4]);
  });

  test("make", ({expect}) => {
    expect.fn(() => make(3, 3)).not.toThrow();
    expect.list(make(3, 3)).toEqual([3, 3, 3]);
  });
});
