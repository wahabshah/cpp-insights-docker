#define BOOST_ASIO_HAS_CO_AWAIT
#define BOOST_ASIO_HAS_STD_COROUTINE
#include <boost/asio.hpp>

using boost::asio::awaitable;
using boost::asio::buffer;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;
awaitable<void> echo(tcp::socket s)
{
    try
    {
        char data[1024];
        for (;;)
        {
            std::size_t n =
            co_await s.async_read_some(
                    buffer(data),
                    use_awaitable);
            co_await async_write(
                s,
                buffer(data, n),
                use_awaitable);
        }
    }
    catch (const std::exception &e)
    {
    }
}
awaitable<void> listen(tcp::acceptor a)
{
    for (;;)
    {
        co_spawn(
            a.get_executor(),
            echo(co_await a.async_accept(use_awaitable)),
            detached);
    }
}
int main()
{
    boost::asio::io_context ctx;
    co_spawn(
        ctx,
        listen({ctx, {tcp::v4(), 1084}}),
        detached);
    ctx.run();
}