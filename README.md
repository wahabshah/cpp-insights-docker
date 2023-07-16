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
* Compile boost asio program1
    * [godbolt link](https://godbolt.org/z/qene9v1We)
    * Build via c++ :-
       ```sh
       /usr/bin/c++ echo-server-perthread.cpp -g -std=c++20   -o echo-server-perthread1 -lpthread
       ```
    * Build via insights :-
       ```sh
       /usr/local/bin/insights echo-server-perthread.cpp -- -std=c++20 -lpthread
       ```
* Compile boost asio program2
    * [godbolt link](https://godbolt.org/z/vvhG6e31P)
    * Build via c++ :-
       ```sh
       /usr/bin/c++ echo-server-coroutine.cpp -g -std=c++20   -o echo-server-coroutine -lpthread
       ```
    * Build via insights :-
       ```sh
       /usr/local/bin/insights echo-server-coroutine.cpp -- -std=c++20 -lpthread
       ```
