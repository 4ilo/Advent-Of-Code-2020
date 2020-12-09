def cc_aoc(name, input_file, example_file, **kwargs):
    native.cc_test(
        name = name + "_example",
        data = [example_file],
        defines = ['INPUT_FILE=\\"{}/{}\\"'.format(name, example_file), "EXAMPLE"],
        **kwargs,
    )
    native.cc_test(
        name = name,
        data = [input_file],
        defines = ['INPUT_FILE=\\"{}/{}\\"'.format(name, input_file)],
        **kwargs,
    )


def py_aoc(name, input_file, example_file, main, srcs=[], **kwargs):
    native.py_test(
        name = name + "_example",
        data = [example_file],
        args = ["$(location {})".format(example_file)],
        srcs = srcs + [main],
        main = main,
        **kwargs,
    )
    native.py_test(
        name = name,
        data = [input_file],
        args = ["$(location {})".format(input_file)],
        srcs = srcs + [main],
        main = main,
        **kwargs,
    )
