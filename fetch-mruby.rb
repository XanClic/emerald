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
# die unless system('cd mruby; git checkout 21310019639d7c6ec13b558ba73766121985950e')


status('Patching build_config.rb...')

content = IO.read('mruby/build_config.rb')

die unless content


content = "# coding: utf-8\n\n" + content + <<-EOS

MRuby::CrossBuild.new('emerald') do |conf|
  toolchain :gcc

  conf.cc.flags << "-std=c11 -m32 -ffreestanding -nostartfiles -nostdinc -nodefaultlibs '-I#{Dir.pwd}/src/include' -DDISABLE_STDIO -DDISABLE_TIME -DMRB_INT64"

  conf.bins = %w()
end
EOS


IO.write('mruby/build_config.rb', content)
