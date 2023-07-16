# cpp-insights-docker

<a href="https://gitpod.io/#https://github.com/wahabshah/cpp-insights-docker" rel="nofollow noopener noreferrer" target="_blank" class="after:hidden"><img src="https://gitpod.io/button/open-in-gitpod.svg" alt="Open in Gitpod"></a>

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://github.com/codespaces/new?hide_repo_select=true&ref=main&repo=667088999&machine=standardLinux32gb&devcontainer_path=.devcontainer%2Fdevcontainer.json&location=WestEurope)

[![Open in Dev Containers](https://img.shields.io/static/v1?label=Dev%20Containers&message=Open&color=blue&logo=visualstudiocode)](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/wahabshah/cpp-insights-docker)


* Test cpp insight
```sh
./build/insights test-cppinsights.cpp -- -std=c++17
```
* [godbolt link](https://godbolt.org/z/En53vYG74)
* Compile
    * Build via c++ :-
    ```sh
    /usr/bin/c++ echo-server-coroutine.cpp -g -std=c++2b -fcoroutines  -o echo-server-coroutine -lpthread
    ```
    * Build via insights :-
    ```sh
    ./build/insights --use-libc++ echo-server-coroutine.cpp -- -std=c++2b -lpthread
    ```