FROM andreasfertig/cppinsights-builder-gitpod:latest

ARG REPO_ROOT=${REPO_ROOT:-/workspace}

USER root
RUN apt update                                                             \
    && apt -y install build-essential cmake libboost-dev sudo strace nano

### Gitpod user ###
RUN userdel gitpod
# '-l': see https://docs.docker.com/develop/develop-images/dockerfile_best-practices/#user
RUN useradd -l -u 33333 -G sudo -md /home/gitpod -s /bin/bash -p gitpod gitpod \
    # passwordless sudo for users in the 'sudo' group
    && sed -i.bkp -e 's/%sudo\s\+ALL=(ALL\(:ALL\)\?)\s\+ALL/%sudo ALL=NOPASSWD:ALL/g' /etc/sudoers \
    # To emulate the workspace-session behavior within dazzle build env
    && mkdir ${REPO_ROOT} && chown -hR gitpod:gitpod ${REPO_ROOT}

### Install cppinsights ## 
RUN git clone https://github.com/andreasfertig/cppinsights.git   /tmp/cppinsights                                                  \
    && mkdir -p /tmp/build                                                                                                         \
    && cd /tmp/build                                                                                                               \
    && cmake -G Ninja -DINSIGHTS_STATIC=Yes -DINSIGHTS_COVERAGE=No -DINSIGHTS_LLVM_CONFIG=/usr/bin/llvm-config /tmp/cppinsights    \
    && ninja -j`nproc`                                                                                                             \
    && ninja install

## Change User ##
USER gitpod
