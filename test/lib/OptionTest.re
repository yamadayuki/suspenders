open TestFramework;

open Suspenders.Option;

describe("Option", ({describe, test}) => {
  let add1 = x => x + 1;

  describe("mapWithDefault", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.int(mapWithDefault(1, add1, Some(1))).toBe(2)
    );

    test("with None", ({expect}) =>
      expect.int(mapWithDefault(1, add1, None)).toBe(1)
    );
  });

  describe("map", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.option(map(add1, Some(1))).toBe(Some(2))
    );

    test("with None", ({expect}) =>
      expect.option(map(add1, None)).toBeNone()
    );
  });

  describe("flatMap", ({test}) => {
    let add1 = x => Some(x + 1);

    test("with Some value", ({expect}) =>
      expect.option(flatMap(add1, Some(1))).toBe(Some(2))
    );

    test("with None", ({expect}) =>
      expect.option(flatMap(add1, None)).toBeNone()
    );
  });

  describe("getWithDefault", ({test}) => {
    test("with Some value", ({expect}) =>
      expect.int(getWithDefault(1, Some(2))).toBe(2)
    );

    test("with Some value", ({expect}) =>
      expect.int(getWithDefault(1, None)).toBe(1)
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
    expect.bool(eq((==), Some(1), Some(1))).toBe(true);
    expect.bool(eq((==), Some(1), None)).toBe(false);
    expect.bool(eq((==), None, Some(1))).toBe(false);
    expect.bool(eq((==), None, None)).toBe(true);
  });

  test("cmp", ({expect}) => {
    expect.int(cmp(compare, Some(1), Some(1))).toBe(0);
    expect.int(cmp(compare, Some(2), None)).toBe(1);
    expect.int(cmp(compare, None, Some(1))).toBe(-1);
    expect.int(cmp(compare, None, None)).toBe(0);
  });
});
