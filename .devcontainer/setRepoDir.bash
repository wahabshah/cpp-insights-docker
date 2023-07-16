#!/bin/bash

if [[ -n "${CODESPACES}" ]]; then                 
export REPO_ROOT="/workspaces/${RepositoryName}"  
else                                              
export REPO_ROOT=${GITPOD_REPO_ROOT}              
fi