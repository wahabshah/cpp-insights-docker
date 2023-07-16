FROM andreasfertig/cppinsights-builder-gitpod:latest

USER root
RUN apt update                \
    && apt -y install libboost-dev sudo strace

RUN env
ARG REPO_ROOT=${GITPOD_REPO_ROOT}
RUN git clone https://github.com/andreasfertig/cppinsights.git   ${REPO_ROOT}/cppinsights                                                  \
    && mkdir -p ${REPO_ROOT}/build                                                                                                         \
    && cd ${REPO_ROOT}/build                                                                                                               \
    && cmake -G Ninja -DINSIGHTS_STATIC=Yes -DINSIGHTS_COVERAGE=No -DINSIGHTS_LLVM_CONFIG=/usr/bin/llvm-config ${REPO_ROOT}/cppinsights    \
    && ninja -j`nproc`