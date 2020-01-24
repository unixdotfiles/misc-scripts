#!/usr/bin/env python
import argparse

SLOW_THRESHOLD = 7


def parse_line(raw_line):
  nonewline = raw_line.strip('\n')
  timestr, rest = nonewline.split(' ', 1)
  return int(timestr), rest


def slow(f):
  count = 0
  start_time, rest = parse_line(f.readline())
  print(f"0 {rest}")

  prev_line = rest
  prev_line_start: int = start_time
  for line in f.readlines():
    count += 1
    if len(line) == 0 or line == "\n":
      continue
    if not line[0].isdigit():
      continue

    try:
      t, rest = parse_line(line)
      diff = t - prev_line_start
      if diff > SLOW_THRESHOLD:
        print(f"{t - start_time} {diff} {prev_line}")
      prev_line_start = t
      prev_line = rest
    except ValueError:
      continue


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("--file", type=argparse.FileType('r'), required=True)
  args = parser.parse_args()
  slow(args.file)


if __name__ == "__main__":
  main()
