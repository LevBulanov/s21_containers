FROM alpine:3.20 AS builder

RUN apk --no-cache --upgrade add \
  gcc \
  g++ \
  musl-dev \
  gtest-dev \
  valgrind

WORKDIR /testing
COPY ./ ./

RUN mkdir -p tests/build \
  && gcc tests/*.cc -lgtest -lgtest_main -lm -lstdc++ -g -Wall -Wextra -Werror -std=c++17 -o tests/build/test_runner

CMD ["valgrind", "tests/build/test_runner"]

