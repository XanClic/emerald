#!/usr/bin/env ruby
# coding: utf-8

def status(msg)
    puts("\033[0;1m#{msg}\033[0m")
end

def die
    puts("\033[0;31;1mFailed\033[0m")
    exit 1
end


status('Cloning mruby git...')

die unless system('git clone git://github.com/mruby/mruby.git')


status('Patching build_config.rb...')

content = IO.read('mruby/build_config.rb')

die unless content


content = "# coding: utf-8\n\n" + content + <<-EOS

MRuby::CrossBuild.new('µxoµcota') do |conf|
  toolchain :gcc

  conf.cc.flags << "-std=c11 -m32 -ffreestanding -nostartfiles -nostdinc -nodefaultlibs '-I#{Dir.pwd}/src/include'"

  conf.bins = %w()
end
EOS


IO.write('mruby/build_config.rb', content)
