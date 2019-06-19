include Rely.Make({
  let config =
    Rely.TestFrameworkConfig.initialize({
      snapshotDir: "./test/__snapshots__",
      projectDir: ".",
    });
});

open RelyInternal__RelyAPI.MatcherTypes;

open ArrayExtensions;
open ListExtensions;

type customMatchers('a) = {
  array: array('a) => arrayExtensions,
  list: list('a) => listExtensions,
};

let customMatchers = createMatcher => {
  array: arr => arrayExtensions(arr, createMatcher),
  list: lst => listExtensions(lst, createMatcher),
};

let {describe, describeOnly, describeSkip} = extendDescribe(customMatchers);
