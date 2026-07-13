#!/bin/bash
# Wrapper for clang++ that uses system linker and libstdc++
exec /home/linuxbrew/.linuxbrew/bin/clang++ -stdlib=libstdc++ -B/usr/bin -L/usr/lib64 -L/home/fuzzbox/.local/lib "$@"
