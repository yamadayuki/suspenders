open TestFramework;
open Suspenders.Array;

describe("Array", ({describe, test}) => {
  describe("swapExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let arr = [|1, 2, 3|];
      expect.fn(() => swapExn(arr, 0, 2)).not.toThrow();
      expect.array(arr).toEqual([|3, 2, 1|]);
    });

    test("throws", ({expect}) => {
      let arr = [|1, 2, 3|];
      expect.fn(() => swapExn(arr, 0, 100)).toThrow();
    });
  });

  test("shuffleInPlace", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => shuffleInPlace(arr)).not.toThrow();
    expect.ext.array(arr).hasMember(1);
    expect.ext.array(arr).hasMember(2);
    expect.ext.array(arr).hasMember(3);
  });

  test("shuffle", ({expect}) => {
    let arr = [|1, 2, 3|];
    let newArr = ref([||]);
    expect.fn(() => newArr := shuffle(arr)).not.toThrow();
    expect.array(arr).toEqual([|1, 2, 3|]);
    expect.ext.array(newArr^).hasMember(1);
    expect.ext.array(newArr^).hasMember(2);
    expect.ext.array(newArr^).hasMember(3);
  });

  test("reverseInPlace", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => reverseInPlace(arr)).not.toThrow();
    expect.array(arr).toEqual([|3, 2, 1|]);
  });

  test("reverse", ({expect}) => {
    let arr = [|1, 2, 3|];
    let newArr = ref([||]);
    expect.fn(() => newArr := reverse(arr)).not.toThrow();
    expect.array(arr).toEqual([|1, 2, 3|]);
    expect.array(newArr^).toEqual([|3, 2, 1|]);
  });

  test("makeBy", ({expect}) => {
    let arr = ref([||]);
    expect.fn(() => arr := makeBy(3, i => i)).not.toThrow();
    expect.array(arr^).toEqual([|0, 1, 2|]);
  });

  test("makeByAndShuffle", ({expect}) => {
    let arr = ref([||]);
    expect.fn(() => arr := makeByAndShuffle(3, i => i)).not.toThrow();
    expect.ext.array(arr^).hasMember(0);
    expect.ext.array(arr^).hasMember(1);
    expect.ext.array(arr^).hasMember(2);
  });

  test("range", ({expect}) => {
    let arr = ref([||]);
    expect.fn(() => arr := range(3, 5)).not.toThrow();
    expect.array(arr^).toEqual([|3, 4, 5|]);
  });

  test("rangeBy", ({expect}) => {
    let arr = ref([||]);
    expect.fn(() => arr := rangeBy(~step=2, 3, 5)).not.toThrow();
    expect.array(arr^).toEqual([|3, 5|]);
  });

  test("rangeBy", ({expect}) => {
    let arr = ref([||]);
    expect.fn(() => arr := rangeBy(~step=2, 3, 5)).not.toThrow();
    expect.array(arr^).toEqual([|3, 5|]);
  });

  test("zip", ({expect}) => {
    let x = [|1, 2, 3|];
    let y = [|4, 5, 6|];
    let arr = ref([||]);
    expect.fn(() => arr := zip(x, y)).not.toThrow();
    expect.array(arr^).toEqual([|(1, 4), (2, 5), (3, 6)|]);
  });

  test("zipBy", ({expect}) => {
    let x = [|1, 2, 3|];
    let y = [|4, 5, 6|];
    let arr = ref([||]);
    expect.fn(() => arr := zipBy((a, b) => a + b, x, y)).not.toThrow();
    expect.array(arr^).toEqual([|5, 7, 9|]);
  });

  test("concatMany", ({expect}) => {
    let x = [|1, 2, 3|];
    let y = [|4, 5, 6|];
    let z = [|7, 8, 9|];
    let arr = ref([||]);
    expect.fn(() => arr := concatMany([|x, y, z|])).not.toThrow();
    expect.array(arr^).toEqual([|1, 2, 3, 4, 5, 6, 7, 8, 9|]);
  });

  test("slice", ({expect}) => {
    let arr = [|1, 2, 3|];
    let newArr = ref([||]);
    expect.fn(() => newArr := slice(1, 2, arr)).not.toThrow();
    expect.array(arr).toEqual([|1, 2, 3|]);
    expect.array(newArr^).toEqual([|2, 3|]);
  });

  test("sliceToEnd", ({expect}) => {
    let arr = [|1, 2, 3|];
    let newArr = ref([||]);
    expect.fn(() => newArr := sliceToEnd(1, arr)).not.toThrow();
    expect.array(arr).toEqual([|1, 2, 3|]);
    expect.array(newArr^).toEqual([|2, 3|]);
  });

  test("fill", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => fill(1, 2, 1, arr)).not.toThrow();
    expect.array(arr).not.toEqual([|1, 2, 3|]);
    expect.array(arr).toEqual([|1, 1, 1|]);
  });

  test("forEach", ({expect}) => {
    let double = x => x * 2 |> ignore;
    let mock = Mock.mock1(double);
    let arr = [|1, 2, 3|];

    expect.fn(() => forEach(Mock.fn(mock), arr)).not.toThrow();
    expect.mock(mock).toBeCalledTimes(3);
  });

  test("forEach", ({expect}) => {
    let double = (i, x) => (i + x) * 2 |> ignore;
    let mock = Mock.mock1(double);
    let arr = [|1, 2, 3|];

    expect.fn(() => forEachi(Mock.fn(mock), arr)).not.toThrow();
    expect.mock(mock).toBeCalledTimes(3);
  });

  test("getBy", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => getBy(x => x == 1, arr)).not.toThrow();
    expect.option(getBy(x => x == 1, arr)).toBe(Some(1));
    expect.option(getBy(x => x == 5, arr)).toBeNone();
  });

  test("getIndexBy", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => getIndexBy(x => x == 1, arr)).not.toThrow();
    expect.option(getIndexBy(x => x == 1, arr)).toBe(Some(0));
    expect.option(getIndexBy(x => x == 5, arr)).toBeNone();
  });

  test("keep", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => keep(x => x mod 2 == 1, arr)).not.toThrow();
    expect.array(keep(x => x mod 2 == 1, arr)).toEqual([|1, 3|]);
  });

  test("keepi", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => keepi((i, x) => x mod 2 == 1, arr)).not.toThrow();
    expect.array(keepi((i, x) => x mod 2 == 1, arr)).toEqual([|1, 3|]);
  });

  test("keepMap", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => keepMap(x => x mod 2 == 1 ? Some(x) : None, arr)).not.
      toThrow();
    expect.array(keepMap(x => x mod 2 == 1 ? Some(x) : None, arr)).toEqual([|
      1,
      3,
    |]);
  });

  test("reduce", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => reduce((acc, x) => acc + x, 0, arr)).not.toThrow();
    expect.int(reduce((acc, x) => acc + x, 0, arr)).toBe(6);
  });

  test("reduceReverse", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => reduceReverse((acc, x) => acc + x, 0, arr)).not.toThrow();
    expect.int(reduceReverse((acc, x) => acc + x, 0, arr)).toBe(6);
  });

  test("reducei", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => reducei((i, acc, x) => acc + x, 0, arr)).not.toThrow();
    expect.int(reducei((i, acc, x) => acc + x, 0, arr)).toBe(6);
  });

  test("reduceReversei", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => reduceReversei((i, acc, x) => acc + x, 0, arr)).not.
      toThrow();
    expect.int(reduceReversei((i, acc, x) => acc + x, 0, arr)).toBe(6);
  });

  test("every", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => every(x => x < 5, arr)).not.toThrow();
    expect.bool(every(x => x < 5, arr)).toBe(true);
    expect.bool(every(x => x > 2, arr)).toBe(false);
  });

  test("some", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => some(x => x < 5, arr)).not.toThrow();
    expect.bool(some(x => x < 5, arr)).toBe(true);
    expect.bool(some(x => x > 5, arr)).toBe(false);
  });

  test("eq", ({expect}) => {
    let xs = [|1, 2, 3|];
    let ys = [|1, 2, 3|];
    expect.fn(() => eq((==), xs, ys)).not.toThrow();
    expect.bool(eq((==), xs, ys)).toBe(true);
  });

  test("cmp", ({expect}) => {
    let xs = [|1, 2, 3|];
    let ys = [|1, 2, 3|];
    expect.fn(() => cmp((x, y) => 1, xs, ys)).not.toThrow();
    expect.int(cmp((x, y) => 0, xs, ys)).toBe(0);
    expect.int(cmp((x, y) => 0, xs, [|1, 2, 3, 4|])).toBe(-1);
  });

  test("partition", ({expect}) => {
    let arr = [|1, 2, 3|];
    expect.fn(() => partition(x => true, arr)).not.toThrow();
    expect.equal(partition(x => x mod 2 == 1, arr), ([|1, 3|], [|2|]));
  });

  test("unzip", ({expect}) => {
    let arr = [|(1, 2), (2, 3), (3, 4)|];
    expect.fn(() => unzip(arr)).not.toThrow();
    expect.equal(unzip(arr), ([|1, 2, 3|], [|2, 3, 4|]));
  });
});
