open Setup;
open TailwindUtils;
open Css_types;
open TestHelpers;

describe("Main testing module", ({test, _}) => {
  test("correct AST for basic selectors", ({expect, _}) => {
    let tailwindCss = {|
      .flex {
        display: flex;
      }

      .flex-row {
        flex-direction: row;
      }
    |};

    let ast = parseStylesheet(tailwindCss);
    let expected_ast = (
      [
        Rule.Style_rule({
          Style_rule.prelude: (
            [
              (Component_value.Delim("."), Location.none),
              (Component_value.Ident("flex"), Location.none),
            ],
            Location.none,
          ),
          block: (
            [
              Declaration_list.Declaration({
                Declaration.name: ("display", Location.none),
                value: (
                  [(Component_value.Ident("flex"), Location.none)],
                  Location.none,
                ),
                important: (false, Location.none),
                loc: Location.none,
              }),
            ],
            Location.none,
          ),
          loc: Location.none,
        }),
        Rule.Style_rule({
          Style_rule.prelude: (
            [
              (Component_value.Delim("."), Location.none),
              (Component_value.Ident("flex-row"), Location.none),
            ],
            Location.none,
          ),
          block: (
            [
              Declaration_list.Declaration({
                Declaration.name: ("flex-direction", Location.none),
                value: (
                  [(Component_value.Ident("row"), Location.none)],
                  Location.none,
                ),
                important: (false, Location.none),
                loc: Location.none,
              }),
            ],
            Location.none,
          ),
          loc: Location.none,
        }),
      ],
      Location.none,
    );

    expect.bool(eq_ast(ast, expected_ast)).toBeTrue();
  });

  test("correct AST for hover", ({expect, _}) => {
    let tailwindCss = {|
      .hover\:bg-mono-100:hover {
        background-color: #FFF;
      }
    |};

    let ast = parseStylesheet(tailwindCss);

    //Css_fmt_printer.dump_stylesheet(Format.std_formatter, ast);

    let expected_ast = (
      [
        Rule.Style_rule({
          Style_rule.prelude: (
            [
              (Component_value.Delim("."), Location.none),
              (Component_value.Ident("hover\:bg-mono-100"), Location.none),
              (Component_value.Delim(":"), Location.none),
              (Component_value.Ident("hover"), Location.none),
            ],
            Location.none,
          ),
          block: (
            [
              Declaration_list.Declaration({
                Declaration.name: ("background-color", Location.none),
                value: (
                  [(Component_value.Hash("FFF"), Location.none),
                  ],
                  Location.none,
                ),
                important: (false, Location.none),
                loc: Location.none,
              }),
            ],
            Location.none,
          ),
          loc: Location.none,
        }),
     ],
      Location.none,
    );

    
   //Css_fmt_printer.dump_stylesheet(Format.std_formatter, expected_ast);

    expect.bool(eq_ast(ast, expected_ast)).toBeTrue();
  });

});


describe("Different types of AST nodes", ({test, _}) => {
  test("Basic selectors", ({expect, _}) => {
    let tailwindCss = {|
      .flex {
        display: flex;
      }

      .flex-row {
        flex-direction: row;
      }
    |};

    let expectedClassNames = ["flex", "flex-row"];
    expect.list(getAcceptableClassNames(tailwindCss)).toEqual(expectedClassNames);
  });

  test("Hover selector", ({expect, _}) => {
    let tailwindCss = {|
      .hover\:bg-mono-100:hover {
        background-color: #FFF;
      }
    |};

    let expectedClassNames = ["hover\:bg-mono-100"];
    expect.list(getAcceptableClassNames(tailwindCss)).toEqual(expectedClassNames);
  })
})
