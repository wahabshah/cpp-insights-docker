FROM andreasfertig/cppinsights-builder-gitpod:latest

RUN apt update \
    && apt install strace

#RUN git clone https://github.com/andreasfertig/cppinsights.git


#- init: "mkdir /workspace/build && cd /workspace/build && cmake -G Ninja -DINSIGHTS_STATIC=Yes -DINSIGHTS_COVERAGE=No -DINSIGHTS_LLVM_CONFIG=/usr/bin/llvm-config /workspace/cppinsights && echo \"Run: ninja -j2\""