#!/usr/bin/env ruby
# coding: utf-8


require 'find'
require 'pathname'


def exec(cmd)
    puts(cmd)
    exit 1 unless system(cmd)
end


if ARGV[0] == 'clean'
    exec("rm -f kernel obj/*.o")
    exit 0
end


incdirs = ['../include', '../../mruby/include']
libdirs = ['../../mruby/build/emerald/lib', File.dirname(`gcc -m32 -print-libgcc-file-name`)]
libs    = ['mruby', 'gcc']

cc = 'gcc'
cflags = "-mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-ssse3 -ffreestanding -nostartfiles -nostdinc -nodefaultlibs -m32 -std=gnu11 -O3 -g2 -Wall -Wextra #{incdirs.map { |d| "'-I#{d}'" } * ' '}"
ld = 'ld'
ldflags = "-entry 0x100000 -T link.ld --nmagic #{libdirs.map { |d| "'-L#{d}'" } * ' '}"
asm = 'fasm'
asmflags = ''
asmout = ''
asmquiet = true
objcp = 'objcopy'
objcpflags = '-I binary -O elf32-i386 -B i386'
tar = 'tar'
tarflags = 'cf'


system('mkdir -p obj')


objs = []
tarl = []


Find.find('.') do |path|
    next unless File.file?(path)

    path = Pathname.new(path).cleanpath.to_s

    next if (path[0..3] == 'obj/') || (File.dirname(path) == '.')


    build_obj = (path[0..4] != 'ruby/') || (path == 'ruby/init.rb')


    if build_obj
        obj = "#{Dir.pwd}/obj/#{path.gsub('/', '__')}.o"
        objs << obj

        next if File.file?(obj) && (File.mtime(obj) > File.mtime(path))
    end


    case File.extname(path)
    when '.c'
        exec("#{cc} #{cflags} -c '#{path}' -o '#{obj}'")
    when '.asm'
        exec("#{asm} #{asmflags} '#{path}' #{asmout} '#{obj}' #{asmquiet ? '&> /dev/null' : ''}")
    when '.rb'
        if build_obj
            exec("cd #{File.dirname(path)} && #{objcp} #{objcpflags} '#{File.basename(path)}' '#{obj}'")
        else
            tarl << path
        end
    end
end


exec("#{ld} #{ldflags} #{objs.map { |o| "'#{o}'" } * ' '} -o kernel #{libs.map { |l| "-l#{l}" } * ' '}")

exec("cd ruby && #{tar} #{tarflags} ../initrd.tar #{tarl.map { |t| "'#{t[5..-1]}'" } * ' '}")
