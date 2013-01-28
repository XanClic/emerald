#!/usr/bin/env ruby
# coding: utf-8

def status(msg)
    puts("\033[0;1m<<< #{msg} >>>\033[0m")
end

def die
    puts("\033[0;31;1m<<< Failed >>>\033[0m")
    exit 1
end


if ARGV[0] == 'distclean'
    system('rm -rf mruby')
    exit 0
end


if !File.directory?('mruby')
    status("Fetching mruby")
    die unless system('./fetch-mruby.rb')
end


status("Building mruby library")
die unless system("make -C mruby #{ARGV.map { |a| "'#{a}'" } * ' '}")
