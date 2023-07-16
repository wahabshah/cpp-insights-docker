FROM andreasfertig/cppinsights-builder-gitpod:latest

RUN printenv
RUN exit -1

USER root
RUN apt update                \
    && apt -y install build-essential cmake libboost-dev sudo strace nano

### Gitpod user ###
# '-l': see https://docs.docker.com/develop/develop-images/dockerfile_best-practices/#user
RUN # useradd -l -u 33333 -G sudo -md /home/gitpod -s /bin/bash -p gitpod gitpod \
    # passwordless sudo for users in the 'sudo' group
    sed -i.bkp -e 's/%sudo\s\+ALL=(ALL\(:ALL\)\?)\s\+ALL/%sudo ALL=NOPASSWD:ALL/g' /etc/sudoers \
    # To emulate the workspace-session behavior within dazzle build env
    && mkdir /workspace && chown -hR gitpod:gitpod /workspace

USER gitpod

ARG REPO_ROOT=${GITPOD_REPO_ROOT:-/workspaces/${RepositoryName}}
RUN git clone https://github.com/andreasfertig/cppinsights.git   ${REPO_ROOT}/cppinsights                                                  \
    && mkdir -p ${REPO_ROOT}/build                                                                                                         \
    && cd ${REPO_ROOT}/build                                                                                                               \
    && cmake -G Ninja -DINSIGHTS_STATIC=Yes -DINSIGHTS_COVERAGE=No -DINSIGHTS_LLVM_CONFIG=/usr/bin/llvm-config ${REPO_ROOT}/cppinsights    \
    && ninja -j`nproc`
