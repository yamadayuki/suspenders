open TestFramework;

open Suspenders.Stack;

describe("Stack", ({describe, test}) => {
  test("make", ({expect}) =>
    expect.equal(make(), {root: None})
  );

  test("push", ({expect}) => {
    let stack = make();
    stack |> push(1);
    expect.equal(stack, {root: Some({head: 1, tail: None})});
  });

  test("clear", ({expect}) => {
    let stack = make();
    stack |> push(1);
    expect.equal(stack, {root: Some({head: 1, tail: None})});
    stack |> clear;
    expect.equal(stack, {root: None});
  });

  test("copy", ({expect}) => {
    let stack = make();
    stack |> push(1);
    expect.equal(stack, {root: Some({head: 1, tail: None})});
    let newStack = copy(stack);
    expect.equal(stack, {root: Some({head: 1, tail: None})});
    expect.notSame(stack, newStack);
  });

  test("top", ({expect}) => {
    let stack = make();
    expect.option(top(stack)).toBeNone();
    stack |> push(1);
    expect.option(top(stack)).toBe(Some(1));
  });

  test("isEmpty", ({expect}) => {
    let stack = make();
    expect.bool(isEmpty(stack)).toBe(true);
    stack |> push(1);
    expect.bool(isEmpty(stack)).toBe(false);
  });

  test("pop", ({expect}) => {
    let stack = make();
    expect.option(pop(stack)).toBeNone();
    stack |> push(1);
    expect.option(pop(stack)).toBe(Some(1));
    expect.option(pop(stack)).toBeNone();
  });

  test("size", ({expect}) => {
    let stack = make();
    expect.int(size(stack)).toBe(0);
    stack |> push(1);
    expect.int(size(stack)).toBe(1);
    stack |> push(1);
    expect.int(size(stack)).toBe(2);
  });

  test("forEach", ({expect}) => {
    let stack = make();
    let sum = ref(0);
    let mock = Mock.mock1(x => sum := sum^ + x);
    stack |> push(1);
    stack |> push(2);
    forEach(Mock.fn(mock), stack);
    expect.int(sum^).toBe(3);
    expect.mock(mock).toBeCalledTimes(2);
  });
});
