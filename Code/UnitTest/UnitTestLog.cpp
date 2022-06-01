#include "UnitTest.h"
#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/color.h>

_TEST_(System, Log, Print)
{
    auto style = fg(fmt::color::red);
    fmt::print(stdout, style, "[{}] [{}] {}\n", "hello", "world", 0);
}
