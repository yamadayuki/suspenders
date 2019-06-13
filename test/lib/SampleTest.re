open TestFramework;

describe("sample", ({test}) =>
  test("a == 1", ({expect}) =>
    expect.int(BeltNative.a).toBe(1)
  )
);
