open TestFramework;
open Suspenders.Queue;

describe("Queue", ({describe, test}) => {
  test("make", ({expect}) =>
    expect.equal(make(), {length: 0, first: None, last: None})
  );

  test("add", ({expect}) => {
    let queue = make();
    expect.fn(() => queue |> add(1)).not.toThrow();
    expect.equal(
      queue,
      {
        length: 1,
        first: Some({content: 1, next: None}),
        last: Some({content: 1, next: None}),
      },
    );
  });

  test("clear", ({expect}) => {
    let queue = make();
    queue |> add(1);
    expect.equal(
      queue,
      {
        length: 1,
        first: Some({content: 1, next: None}),
        last: Some({content: 1, next: None}),
      },
    );
    expect.fn(() => queue |> clear).not.toThrow();
    expect.equal(queue, {length: 0, first: None, last: None});
  });

  test("peek", ({expect}) => {
    let queue = make();
    queue |> add(1);
    expect.fn(() => queue |> peek).not.toThrow();
    expect.option(queue |> peek).toBeSome();
    expect.option(queue |> peek).toBe(Some(1));
  });

  describe("peekExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let queue = make();
      queue |> add(1);
      expect.fn(() => peekExn(queue)).not.toThrow();
      expect.int(peekExn(queue)).toBe(1);
    });

    test("throws", ({expect}) => {
      let queue = make();
      expect.fn(() => peekExn(queue)).toThrow();
    });
  });

  test("pop", ({expect}) => {
    let queue = make();
    queue |> add(1);
    let n = ref(Some(0));
    expect.fn(() => n := queue |> pop).not.toThrow();
    expect.option(n^).toBeSome();
    expect.option(n^).toBe(Some(1));
  });

  describe("popExn", ({test}) => {
    test("doesn't throw", ({expect}) => {
      let queue = make();
      queue |> add(1);
      let n = ref(0);
      expect.fn(() => n := popExn(queue)).not.toThrow();
      expect.int(n^).toBe(1);
    });

    test("throws", ({expect}) => {
      let queue = make();
      expect.fn(() => popExn(queue)).toThrow();
    });
  });

  test("copy", ({expect}) => {
    let queue = make();
    queue |> add(1);
    expect.equal(
      queue,
      {
        length: 1,
        first: Some({content: 1, next: None}),
        last: Some({content: 1, next: None}),
      },
    );
    let newStack = copy(queue);
    expect.equal(
      queue,
      {
        length: 1,
        first: Some({content: 1, next: None}),
        last: Some({content: 1, next: None}),
      },
    );
    expect.notSame(queue, newStack);
  });

  test("map", ({expect}) => {
    let queue = make();
    let mock = Mock.mock1(x => x * 2);
    queue |> add(1);
    queue |> add(2);
    expect.equal(
      map(Mock.fn(mock), queue),
      {
        length: 2,
        first: Some({content: 2, next: Some({content: 4, next: None})}),
        last: Some({content: 4, next: None}),
      },
    );
    expect.equal(
      queue,
      {
        length: 2,
        first: Some({content: 1, next: Some({content: 2, next: None})}),
        last: Some({content: 2, next: None}),
      },
    );
    expect.mock(mock).toBeCalledTimes(2);
  });

  test("isEmpty", ({expect}) => {
    let queue = make();
    expect.bool(isEmpty(queue)).toBe(true);
    queue |> add(1);
    expect.bool(isEmpty(queue)).toBe(false);
  });

  test("size", ({expect}) => {
    let queue = make();
    expect.int(size(queue)).toBe(0);
    queue |> add(1);
    expect.int(size(queue)).toBe(1);
    queue |> add(1);
    expect.int(size(queue)).toBe(2);
  });

  test("forEach", ({expect}) => {
    let queue = make();
    let sum = ref(0);
    let mock = Mock.mock1(x => sum := sum^ + x);
    queue |> add(1);
    queue |> add(2);
    forEach(Mock.fn(mock), queue);
    expect.int(sum^).toBe(3);
    expect.mock(mock).toBeCalledTimes(2);
  });

  test("reduce", ({expect}) => {
    let queue = make();
    let mock = Mock.mock1((acc, x) => acc + x);
    queue |> add(1);
    queue |> add(2);
    expect.int(reduce(Mock.fn(mock), 0, queue)).toBe(3);
    expect.equal(
      queue,
      {
        length: 2,
        first: Some({content: 1, next: Some({content: 2, next: None})}),
        last: Some({content: 2, next: None}),
      },
    );
  });

  test("transfer", ({expect}) => {
    let queue = make();
    queue |> add(1);
    queue |> add(2);
    let newQueue = make();
    expect.equal(
      queue,
      {
        length: 2,
        first: Some({content: 1, next: Some({content: 2, next: None})}),
        last: Some({content: 2, next: None}),
      },
    );
    expect.equal(newQueue, {length: 0, first: None, last: None});
    transfer(queue, newQueue);
    expect.notEqual(queue, newQueue);
    expect.equal(queue, {length: 0, first: None, last: None});
    expect.equal(
      newQueue,
      {
        length: 2,
        first: Some({content: 1, next: Some({content: 2, next: None})}),
        last: Some({content: 2, next: None}),
      },
    );
  });

  test("toArray", ({expect}) => {
    let queue = make();
    queue |> add(1);
    queue |> add(2);
    expect.array(toArray(queue)).toEqual([|1, 2|]);
  });

  test("fromArray", ({expect}) =>
    expect.equal(
      fromArray([|1, 2|]),
      {
        length: 2,
        first: Some({content: 1, next: Some({content: 2, next: None})}),
        last: Some({content: 2, next: None}),
      },
    )
  );
});
