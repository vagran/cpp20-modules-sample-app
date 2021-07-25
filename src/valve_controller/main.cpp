export module main;

import std.core;
import tmp;
import adk.common;
import adk.common.MessageComposer;

#include <adk/log.h>

class TestCommitter {
public:
    constexpr bool
    IsEnabled() const
    {
        return true;
    }

    void
    Commit(const char *msg)
    {
        TestLog(msg);
    }
};

class MyComposer: public adk::MessageComposer<TestCommitter> {
public:
    MyComposer():
        adk::MessageComposer<TestCommitter>(TestCommitter())
    {}
};

export int
main(int argc, char **argv)
{
    Test();
    TestLog(std::string("aaa"));

    MyComposer() << "bbb " << 42 << " " << 3.14 << " " << -1_sz << " " << true << " " << argv;
    MyComposer() << false;
}
