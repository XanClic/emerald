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

# If anything should break in future mruby versions, comment this line in
# (on a different note: Update the hash as often as possible)
# die unless system('cd mruby; git checkout 0410bb7623a27ac427f190e3144c85b6446bec05')


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
