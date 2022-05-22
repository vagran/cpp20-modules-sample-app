module tmp;

import std.io;


void
Test()
{
    std::cout << "test " << Internal() << " " << Internal2() << "\n";

    // Clang 14 still fails this test, callback 1 is called twice.
    ([](){ std::cout << "callback 1\n"; })();
    ([](){ std::cout << "callback 2\n"; })();
}
