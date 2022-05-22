module;

#include <csignal>

export module main;

import std.core;
import tmp;
import adk.common;
import adk.common.MessageComposer;
import adk.common.exceptions;
import asio;

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

class MyPayload {
public:
    MyPayload(const std::string_view &s):
        s(s)
    {}

    MyPayload(const MyPayload &o):
        s(o.s)
    {
        LOG << "copied";
    }

    MyPayload(MyPayload &&o):
        s(std::move(o.s))
    {
        LOG << "moved";
    }

    std::string s;
};

class MyException: public adk::Exception {
public:
    using TParamsTuple = std::tuple<MyPayload>;

    MyException(const std::string_view &msg, MyPayload &&payload):
        adk::Exception(std::string(msg) + std::string(" ") + payload.s),
        payload(std::move(payload))
    {}

    MyPayload payload;
};

void
TestThrow()
{
    try {
        try {
    //        adk::TODO("some feature wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
            adk::Throw<MyException>().Params(MyPayload("pld")) << "some message";
        } catch (adk::Exception &e) {
            e.AddSuppressed(adk::InvalidOpException("bad op"));
            adk::Throw<adk::InternalErrorException>().Nested() << "this is nested";
        }
    } catch (...) {
        LOG << std::current_exception();
    }
}

asio::awaitable<void>
MainTask()
{
    LOG << "In main task";
//    adk::TODO("aaa");
    co_return;
}

void
SubscribeSignals(asio::signal_set &signals, asio::io_context &mainCtx)
{
    signals.async_wait([&](asio::error_code ec, int sig) {
        if (ec) {
            LOG.Error() << "Signal error: " << ec.message();
        } else {
            LOG.Info() << "Signal received: " << sig;
        }
        if (sig == SIGUSR1) {
            /* SIGUSR1 can be used here for some diagnostics dumps. */
            SubscribeSignals(signals, mainCtx);
            return;
        }
        LOG.Info() << "Exiting on signal " << sig;
        //XXX stop application instance
        mainCtx.stop();
    });
}

int
RunMain()
{
    asio::io_context mainCtx;
    int exitCode = 0;

    asio::signal_set signals(mainCtx, SIGINT, SIGTERM, SIGUSR1);
    SubscribeSignals(signals, mainCtx);

    asio::co_spawn(mainCtx, MainTask(),
        [&](std::exception_ptr error) {

        if (error) {
            LOG.Error() << error;
        }
        LOG << "stopping";//XXX
        mainCtx.stop();
    });

    LOG << "run";//XXX
    mainCtx.run();

    return exitCode;
}

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

//    TestThrow();

    int exitCode = RunMain();

    adk::Log::Shutdown();
    LOG << "after shutdown";

    return exitCode;
}
