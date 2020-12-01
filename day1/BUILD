cc_test(
    name = "day1_example",
    srcs = [
        "main.c",
    ],
    data = [
        "example.txt",
    ],
    defines = [
        'INPUT_FILE=\\"day1/example.txt\\"',
    ],
    deps = [
        "//common:utils",
    ],
)

cc_test(
    name = "day1",
    srcs = [
        "main.c",
    ],
    data = [
        "input.txt",
    ],
    defines = [
        'INPUT_FILE=\\"day1/input.txt\\"',
    ],
    deps = [
        "//common:utils",
    ],
)

test_suite(
    name = "all",
    tests = [
        ":day1",
        ":day1_example",
    ]
)
