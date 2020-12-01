def cc_aoc(name, input_file, example_file, **kwargs):
    native.cc_test(
        name = name + "_example",
        data = [example_file],
        defines = ['INPUT_FILE=\\"{}/{}\\"'.format(name, example_file)],
        **kwargs,
    )
    native.cc_test(
        name = name,
        data = [input_file],
        defines = ['INPUT_FILE=\\"{}/{}\\"'.format(name, input_file)],
        **kwargs,
    )

    native.test_suite(
        name = "all",
        tests = [
            ":" + name,
            ":" + name + "_example",
        ]
    )
