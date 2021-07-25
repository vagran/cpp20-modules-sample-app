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
    Commit(const std::string_view &msg)
    {
        LOG << msg;
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
    LOG << "before initialize";
    adk::Log::Initialize(adk::Log::Configuration(adk::Log::Level::DEBUG));

    using namespace std::string_literals;

    Test();

    MyComposer() << "bbb "s << 42 << " " << 3.14 << " " << -1_sz << " " << true << " " << argv;
    MyComposer() << false;

    adk::Logger log = adk::Log::GetLoggerS("MyLogger");
    log.Write(adk::Log::Level::INFO, "test");

    LOG.Warning() << "Test warning " << 43;

    adk::Log::Shutdown();
    LOG << "after shutdown";
}
