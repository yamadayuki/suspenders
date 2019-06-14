open TestFramework;

open Suspenders.BOption;

describe("BOption", ({describe, test}) => {
  let add1 = x => x + 1;

  describe("mapWithDefault", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.int(mapWithDefault(Some(1), 1, add1)).toBe(2)
    );

    test("with None", ({expect}) =>
      expect.int(mapWithDefault(None, 1, add1)).toBe(1)
    );
  });

  describe("map", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.option(map(Some(1), add1)).toBe(Some(2))
    );

    test("with None", ({expect}) =>
      expect.option(map(None, add1)).toBeNone()
    );
  });

  describe("flatMap", ({test}) => {
    let add1 = x => Some(x + 1);

    test("with Some value", ({expect}) =>
      expect.option(flatMap(Some(1), add1)).toBe(Some(2))
    );

    test("with None", ({expect}) =>
      expect.option(flatMap(None, add1)).toBeNone()
    );
  });

  describe("getWithDefault", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.int(getWithDefault(Some(2), 1)).toBe(2)
    );

    test("with Some value", ({expect}) =>
      expect.int(getWithDefault(None, 1)).toBe(1)
    );
  });

  describe("isSome", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.bool(isSome(Some(1))).toBe(true)
    );

    test("with Some value", ({expect}) =>
      expect.bool(isSome(None)).toBe(false)
    );
  });

  describe("isNone", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.bool(isNone(Some(1))).toBe(false)
    );

    test("with Some value", ({expect}) =>
      expect.bool(isNone(None)).toBe(true)
    );
  });

  test("eq", ({expect}) => {
    expect.bool(eq(Some(1), Some(1), (==))).toBe(true);
    expect.bool(eq(Some(1), None, (==))).toBe(false);
    expect.bool(eq(None, Some(1), (==))).toBe(false);
    expect.bool(eq(None, None, (==))).toBe(true);
  });

  test("cmp", ({expect}) => {
    expect.int(cmp(Some(1), Some(1), compare)).toBe(0);
    expect.int(cmp(Some(2), None, compare)).toBe(1);
    expect.int(cmp(None, Some(1), compare)).toBe(-1);
    expect.int(cmp(None, None, compare)).toBe(0);
  });
});
