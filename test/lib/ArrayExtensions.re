open RelyInternal__RelyAPI.MatcherTypes;

type arrayExtensions = {hasMember: int => unit};

let arrayExtensions = (actual, {createMatcher}) => {
  let pass = (() => "", true);
  let createHasMemberMatcher =
    createMatcher(
      ({formatReceived, formatExpected}, actualThunk, expectedThunk) => {
      let actual = actualThunk();
      let expected = expectedThunk();
      let actualIsMember = Array.mem(expected, actual);

      if (actualIsMember) {
        pass;
      } else {
        let failureMessage =
          String.concat(
            "",
            [
              "Expected: ",
              formatExpected(string_of_int(expected)),
              "\n",
              "Expected value is not member of: ",
              formatReceived(RelyInternal.PolymorphicPrint.print(actual)),
            ],
          );
        (() => failureMessage, false);
      };
    });
  {
    hasMember: expected =>
      createHasMemberMatcher(() => actual, () => expected),
  };
};
