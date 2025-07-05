FROM ubuntu:22.04

# タイムゾーン設定で対話を避ける
ENV DEBIAN_FRONTEND=noninteractive

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    gdb \
    git \
    vim \
    curl \
    unzip \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# MinGW64 環境をインストール (Windows互換)
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    mingw-w64-tools \
    && rm -rf /var/lib/apt/lists/*

# AtCoder Library (ACL) をインストール
RUN mkdir -p /opt/ac-library && \
    cd /opt/ac-library && \
    curl -L https://github.com/atcoder/ac-library/releases/latest/download/ac-library.zip -o ac-library.zip && \
    unzip ac-library.zip && \
    find . -name "*.hpp" -exec cp {} /usr/local/include/ \; && \
    find . -name "*.hpp" -exec cp {} /usr/x86_64-w64-mingw32/include/ \; && \
    rm -rf ac-library.zip

# 環境変数を設定
ENV CC=gcc
ENV CXX=g++
ENV MINGW_CC=x86_64-w64-mingw32-gcc
ENV MINGW_CXX=x86_64-w64-mingw32-g++

# 作業ディレクトリを設定
WORKDIR /workspace

# outputディレクトリを作成
RUN mkdir -p /workspace/output

# デフォルトのシェルを設定
CMD ["/bin/bash"]