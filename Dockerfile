FROM ubuntu

RUN yes | unminimize && \
  apt-get update && \
  apt-get install --yes \
    man \
    man-db \
    manpages-posix
