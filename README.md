# cpp-insights-docker

<a href="https://gitpod.io/#https://github.com/wahabshah/cpp-insights-docker" rel="nofollow noopener noreferrer" target="_blank" class="after:hidden"><img src="https://gitpod.io/button/open-in-gitpod.svg" alt="Open in Gitpod"></a>

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://github.com/codespaces/new?hide_repo_select=true&ref=main&repo=667088999&machine=standardLinux32gb&devcontainer_path=.devcontainer%2Fdevcontainer.json&location=WestEurope)

[![Open in Dev Containers](https://img.shields.io/static/v1?label=Dev%20Containers&message=Open&color=blue&logo=visualstudiocode)](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/wahabshah/cpp-insights-docker)

* The goal of this repository is to test cpp-insights with asio library
  * To check how the header only library is actually compiled in the background
* Compile test program1:-
    ```sh
    /usr/local/bin/insights test-cppinsights.cpp -- -std=c++17
    ```
    ```cpp
    class Base
    {
    public: 
    // inline constexpr Base() noexcept = default;
    };



    class Derived : public Base
    {
    public: 
    // inline constexpr Derived() noexcept = default;
    };



    int main()
    {
    Derived d;
    Base & b = static_cast<Base&>(d);
    return 0;
    }
    ```
* Compile boost asio program2
    * [godbolt link](https://godbolt.org/z/qene9v1We)
    * Build via c++ :-
       ```sh
       /usr/bin/c++ echo-server-perthread.cpp -g -std=c++20   -o echo-server-perthread1 -lpthread
       ```
    * Build via insights :-
       ```sh
       /usr/local/bin/insights echo-server-perthread.cpp -- -std=c++20 -lpthread
       ```
       <details>
        <summary>Toggle me!</summary>
        ```cpp
        #include <boost/asio.hpp>
        #include <iostream>
        #include <thread>

        void echo(boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > socket)
        {
        char data[128];
        for(; ; ) {
            std::operator<<(std::operator<<(std::cout, "echo function : "), std::this_thread::get_id()).operator<<(std::endl);
            std::size_t bytesReceived = socket.read_some<boost::asio::mutable_buffers_1>(boost::asio::buffer(data));
            std::operator<<(std::operator<<(std::operator<<(std::cout, "received ").operator<<(bytesReceived), " "), data).operator<<(std::endl);
            unsigned long bytesSent = boost::asio::write(socket, boost::asio::buffer(data, bytesReceived), 0);
            std::operator<<(std::operator<<(std::operator<<(std::cout, "sent ").operator<<(bytesSent), " "), data).operator<<(std::endl);
        }
        
        }



        void listen(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > acceptor)
        {
        for(; ; ) {
            std::operator<<(std::operator<<(std::cout, "listen 1: "), std::this_thread::get_id()).operator<<(std::endl);
            std::thread(echo, acceptor.accept()).detach();
            std::operator<<(std::operator<<(std::cout, "listen 2: "), std::this_thread::get_id()).operator<<(std::endl);
        }
        
        }


        int main()
        {
        const int port = 1083;
        std::operator<<(std::operator<<(std::operator<<(std::operator<<(std::cout, "Echo Server - Perthread "), "@").operator<<(port), " "), std::this_thread::get_id()).operator<<(std::endl);
        boost::asio::io_context io = boost::asio::io_context();
        listen(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > >(io, boost::asio::ip::basic_endpoint<boost::asio::ip::tcp>(boost::asio::ip::tcp::v4(), static_cast<unsigned short>(port)), true, 0));
        std::operator<<(std::operator<<(std::cout, "Server about to end: "), std::this_thread::get_id()).operator<<(std::endl);
        return 0;
        }
        ```
       </details>
* Compile boost asio program3
    * [godbolt link](https://godbolt.org/z/vvhG6e31P)
    * Build via c++ :-
       ```sh
       /usr/bin/c++ echo-server-coroutine.cpp -g -std=c++20   -o echo-server-coroutine -lpthread
       ```
    * Build via insights :-
       ```sh
       /usr/local/bin/insights echo-server-coroutine.cpp -- -std=c++20 -lpthread
       ```
       <details>
       <summary>Toggle me!</summary>

       ```cpp
        In file included from /workspace/cpp-insights-docker/echo-server-coroutine.cpp:3:
        In file included from /usr/include/boost/asio.hpp:23:
        /usr/include/boost/asio/awaitable.hpp:68:14: error: no member named 'exchange' in namespace 'std'; did you mean 'std::__atomic_impl::exchange'?
            : frame_(std::exchange(other.frame_, nullptr))
                    ^~~~~
        /usr/lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits/atomic_base.h:976:7: note: 'std::__atomic_impl::exchange' declared here
            exchange(_Tp* __ptr, _Val<_Tp> __desired, memory_order __m) noexcept
            ^
        In file included from /workspace/cpp-insights-docker/echo-server-coroutine.cpp:3:
        In file included from /usr/include/boost/asio.hpp:23:
        /usr/include/boost/asio/awaitable.hpp:68:14: error: no matching function for call to 'exchange'
            : frame_(std::exchange(other.frame_, nullptr))
                    ^~~~~~~~~~~~~
        /usr/include/boost/asio/impl/awaitable.hpp:153:12: note: in instantiation of member function 'boost::asio::awaitable<unsigned long>::awaitable' requested here
            return a;
                ^
        /usr/lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits/atomic_base.h:976:7: note: candidate function template not viable: requires 3 arguments, but 2 were provided
            exchange(_Tp* __ptr, _Val<_Tp> __desired, memory_order __m) noexcept
            ^
        In file included from /workspace/cpp-insights-docker/echo-server-coroutine.cpp:3:
        In file included from /usr/include/boost/asio.hpp:23:
        /usr/include/boost/asio/awaitable.hpp:68:14: error: no matching function for call to 'exchange'
            : frame_(std::exchange(other.frame_, nullptr))
                    ^~~~~~~~~~~~~
        /usr/include/boost/asio/impl/awaitable.hpp:153:12: note: in instantiation of member function 'boost::asio::awaitable<boost::asio::basic_stream_socket<boost::asio::ip::tcp>>::awaitable' requested here
            return a;
                ^
        /usr/lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits/atomic_base.h:976:7: note: candidate function template not viable: requires 3 arguments, but 2 were provided
            exchange(_Tp* __ptr, _Val<_Tp> __desired, memory_order __m) noexcept
            ^
        In file included from /workspace/cpp-insights-docker/echo-server-coroutine.cpp:3:
        In file included from /usr/include/boost/asio.hpp:23:
        /usr/include/boost/asio/awaitable.hpp:68:14: error: no matching function for call to 'exchange'
            : frame_(std::exchange(other.frame_, nullptr))
                    ^~~~~~~~~~~~~
        /usr/include/boost/asio/impl/co_spawn.hpp:260:41: note: in instantiation of member function 'boost::asio::awaitable<void>::awaitable' requested here
        return (co_spawn)(ctx.get_executor(), std::move(a),
                                                ^
        /usr/lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits/atomic_base.h:976:7: note: candidate function template not viable: requires 3 arguments, but 2 were provided
            exchange(_Tp* __ptr, _Val<_Tp> __desired, memory_order __m) noexcept
            ^
        #define BOOST_ASIO_HAS_CO_AWAIT
        #define BOOST_ASIO_HAS_STD_COROUTINE
        #include <boost/asio.hpp>

        using boost::asio::awaitable;
        using boost::asio::buffer;
        using boost::asio::detached;
        using boost::asio::use_awaitable;
        using boost::asio::ip::tcp;
        boost::asio::awaitable<void, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > echo(boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > s)
        {
        try 
        {
            char data[1024];
            for(; ; ) {
            std::size_t n = co_await static_cast<const boost::asio::detail::awaitable_frame_base<boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > >&>(__promise).await_transform<unsigned long>(s.async_read_some<boost::asio::mutable_buffers_1, const boost::asio::use_awaitable_t<boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > &>(boost::asio::buffer(data), boost::asio::use_awaitable));
            co_await static_cast<const boost::asio::detail::awaitable_frame_base<boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > >&>(__promise).await_transform<unsigned long>(boost::asio::async_write(s, boost::asio::buffer(data, n), boost::asio::use_awaitable, 0));
            }
            
        } catch(const std::exception & e) {
        }
        ;
        }

        boost::asio::awaitable<void, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > listen(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > a)
        {
        for(; ; ) {
            boost::asio::co_spawn(a.get_executor(), echo(co_await static_cast<const boost::asio::detail::awaitable_frame_base<boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > >&>(__promise).await_transform<boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > >(a.async_accept<const boost::asio::use_awaitable_t<boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > > &>(boost::asio::use_awaitable))), boost::asio::detached, 0);
        }
        
        }

        int main()
        {
        boost::asio::io_context ctx = boost::asio::io_context();
        boost::asio::co_spawn(ctx, listen(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp, boost::asio::execution::any_executor<boost::asio::execution::context_as_t<boost::asio::execution_context &>, boost::asio::execution::detail::blocking::never_t<0>, boost::asio::execution::prefer_only<boost::asio::execution::detail::blocking::possibly_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::tracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::outstanding_work::untracked_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::fork_t<0> >, boost::asio::execution::prefer_only<boost::asio::execution::detail::relationship::continuation_t<0> > > >{ctx, boost::asio::ip::basic_endpoint<boost::asio::ip::tcp>{boost::asio::ip::tcp::v4(), 1084}, true, 0}), boost::asio::detached, 0);
        ctx.run();
        return 0;
        }
        4 errors generated.
        Error while processing /workspace/cpp-insights-docker/echo-server-coroutine.cpp.
       ```
       </details>
