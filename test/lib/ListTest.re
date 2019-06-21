open TestFramework;
open Suspenders.List;

describe("List", ({describe}) => {
  describe("Getter and setter", ({describe, test}) => {
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

    test("add", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => add(0, list)).not.toThrow();
      expect.list(add(0, list)).toEqual([0, 1, 2, 3]);
    });
  });

  describe("Transformation", ({test}) => {
    test("fromArray", ({expect}) => {
      expect.fn(() => fromArray([|1, 2, 3|])).not.toThrow();
      expect.list(fromArray([|1, 2, 3|])).toEqual([1, 2, 3]);
    });

    test("toArray", ({expect}) => {
      expect.fn(() => toArray([1, 2, 3])).not.toThrow();
      expect.array(toArray([1, 2, 3])).toEqual([|1, 2, 3|]);
    });
  });

  describe("Manipulation", ({test}) => {
    test("take", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => take(2, list)).not.toThrow();
      expect.option(take(2, list)).toBe(Some([1, 2]));
    });

    test("drop", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => drop(2, list)).not.toThrow();
      expect.option(drop(2, list)).toBe(Some([3]));
    });

    test("splitAt", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => splitAt(2, list)).not.toThrow();
      expect.option(splitAt(2, list)).toBe(Some(([1, 2], [3])));
    });

    test("shuffle", ({expect}) => {
      let list = [1, 2, 3];
      let newList = ref([]);
      expect.fn(() => newList := shuffle(list)).not.toThrow();
      expect.list(list).toEqual([1, 2, 3]);
      expect.ext.list(newList^).hasMember(1);
      expect.ext.list(newList^).hasMember(2);
      expect.ext.list(newList^).hasMember(3);
    });

    test("unique", ({expect}) => {
      let list = [1, 1, 2, 3, 5, 8, 8];
      expect.fn(() => unique(list)).not.toThrow();
      expect.list(unique(list)).toEqual([1, 2, 3, 5, 8]);
    });

    test("reverse", ({expect}) => {
      let list = [1, 2, 3];
      let newList = ref([]);
      expect.fn(() => newList := reverse(list)).not.toThrow();
      expect.list(list).toEqual([1, 2, 3]);
      expect.list(newList^).toEqual([3, 2, 1]);
    });

    test("keep", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => keep(x => x mod 2 == 1, list)).not.toThrow();
      expect.list(keep(x => x mod 2 == 1, list)).toEqual([1, 3]);
    });

    test("keepi", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => keepi((i, x) => x mod 2 == 1, list)).not.toThrow();
      expect.list(keepi((i, x) => x mod 2 == 1, list)).toEqual([1, 3]);
    });

    test("keepMap", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => keepMap(x => x mod 2 == 1 ? Some(x) : None, list)).not.
        toThrow();
      expect.list(keepMap(x => x mod 2 == 1 ? Some(x) : None, list)).toEqual([
        1,
        3,
      ]);
    });

    test("slice", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => slice(1, 2, list)).not.toThrow();
      expect.list(slice(1, 2, list)).toEqual([2, 3]);
    });

    test("sliceToEnd", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => sliceToEnd(1, list)).not.toThrow();
      expect.list(sliceToEnd(1, list)).toEqual([2, 3]);
    });

    describe("swapExn", ({test}) => {
      test("doesn't throw", ({expect}) => {
        let list = [1, 1, 2, 3];
        expect.fn(() => swapExn(list, 0, 2)).not.toThrow();
        expect.list(swapExn(list, 0, 2)).toEqual([2, 1, 1, 3]);
      });

      test("throws", ({expect}) => {
        let list = [1, 1, 2, 3];
        expect.fn(() => swapExn(list, 0, 5)).toThrow();
      });
    });
  });

  describe("Initialization", ({test}) => {
    test("makeBy", ({expect}) => {
      expect.fn(() => makeBy(3, x => x * x)).not.toThrow();
      expect.list(makeBy(3, x => x * x)).toEqual([0, 1, 4]);
    });

    test("make", ({expect}) => {
      expect.fn(() => make(3, 3)).not.toThrow();
      expect.list(make(3, 3)).toEqual([3, 3, 3]);
    });

    test("range", ({expect}) => {
      expect.fn(() => range(3, 5)).not.toThrow();
      expect.list(range(3, 5)).toEqual([3, 4, 5]);
    });

    test("rangeBy", ({expect}) => {
      expect.fn(() => rangeBy(~step=2, 3, 5)).not.toThrow();
      expect.list(rangeBy(~step=2, 3, 5)).toEqual([3, 5]);
    });
  });

  describe("Iterator", ({test}) => {
    test("mapReverse", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => mapReverse(x => x * x, list)).not.toThrow();
      expect.list(mapReverse(x => x * x, list)).toEqual([9, 4, 1]);
    });

    test("forEach", ({expect}) => {
      let double = x => ();
      let mock = Mock.mock1(double);
      let list = [1, 2, 3];

      expect.fn(() => forEach(Mock.fn(mock), list)).not.toThrow();
      expect.mock(mock).toBeCalledTimes(3);
    });

    test("forEachi", ({expect}) => {
      let double = (i, x) => ();
      let mock = Mock.mock1(double);
      let list = [1, 2, 3];

      expect.fn(() => forEachi(Mock.fn(mock), list)).not.toThrow();
      expect.mock(mock).toBeCalledTimes(3);
    });

    test("reduce", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => reduce((acc, x) => acc + x, 0, list)).not.toThrow();
      expect.int(reduce((acc, x) => acc + x, 0, list)).toBe(6);
    });

    test("reduceReverse", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => reduceReverse((acc, x) => acc + x, 0, list)).not.
        toThrow();
      expect.int(reduceReverse((acc, x) => acc + x, 0, list)).toBe(6);
    });

    test("reducei", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => reducei((i, acc, x) => acc + x, 0, list)).not.toThrow();
      expect.int(reducei((i, acc, x) => acc + x, 0, list)).toBe(6);
    });

    test("reduceReversei", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => reduceReversei((i, acc, x) => acc + x, 0, list)).not.
        toThrow();
      expect.int(reduceReversei((i, acc, x) => acc + x, 0, list)).toBe(6);
    });
  });

  describe("Scanning", ({test}) => {
    test("every", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => every(x => x < 5, list)).not.toThrow();
      expect.bool(every(x => x < 5, list)).toBe(true);
      expect.bool(every(x => x > 2, list)).toBe(false);
    });

    test("some", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => some(x => x < 5, list)).not.toThrow();
      expect.bool(some(x => x < 5, list)).toBe(true);
      expect.bool(some(x => x > 5, list)).toBe(false);
    });

    test("eq", ({expect}) => {
      let xs = [1, 2, 3];
      let ys = [1, 2, 3];
      expect.fn(() => eq((==), xs, ys)).not.toThrow();
      expect.bool(eq((==), xs, ys)).toBe(true);
    });

    test("cmp", ({expect}) => {
      let xs = [1, 2, 3];
      let ys = [1, 2, 3];
      expect.fn(() => cmp((x, y) => 1, xs, ys)).not.toThrow();
      expect.int(cmp((x, y) => 0, xs, ys)).toBe(0);
      expect.int(cmp((x, y) => 0, xs, [1, 2, 3, 4])).toBe(-1);
    });
  });

  describe("Lists of pairs", ({test}) => {
    test("partition", ({expect}) => {
      let list = [1, 2, 3];
      expect.fn(() => partition(x => true, list)).not.toThrow();
      expect.equal(partition(x => x mod 2 == 1, list), ([1, 3], [2]));
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

    test("zipBy", ({expect}) => {
      let xs = [1, 2, 3];
      let ys = [4, 5, 6, 7];
      expect.fn(() => zipBy((x, y) => x + y, xs, ys)).not.toThrow();
      expect.list(zipBy((x, y) => x + y, xs, ys)).toEqual([5, 7, 9]);
    });
  });
});
