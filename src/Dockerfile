FROM alpine:3.20 AS builder

RUN apk --no-cache --upgrade add \
  gcc \
  g++ \
  make \
  musl-dev \
  gtest-dev \
  valgrind

WORKDIR /testing
COPY ./ ./

RUN make clean
RUN make check_valgrind
