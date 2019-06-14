include Rely.Make({
  let config =
    Rely.TestFrameworkConfig.initialize({
      snapshotDir: "./test/__snapshots__",
      projectDir: ".",
    });
});

open RelyInternal__RelyAPI.MatcherTypes;

open ArrayExtensions;

type customMatchers('a) = {array: array('a) => arrayExtensions};

let customMatchers = createMatcher => {
  array: arr => arrayExtensions(arr, createMatcher),
};

let {describe, describeOnly, describeSkip} = extendDescribe(customMatchers);
