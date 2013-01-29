#!/usr/bin/env ruby
# coding: utf-8


def exec(cmd)
    puts(cmd)
    exit 1 unless system(cmd)
end


if ARGV[0] == 'clean'
    exec("rm -f lib?.a obj/*.o")
    exit 0
end


cc = 'gcc'
cflags = '-ffreestanding -nostartfiles -nostdinc -nodefaultlibs -m32 -std=c11 -O3 -Wall -Wextra -pedantic -I../../include'
ar = 'ar'
arflags = 'rcs'
asm = 'fasm'
asmflags = ''
asmout = ''
asmquiet = true


system('mkdir -p obj')


objs = []


Dir.new('.').each do |dir|
    next unless File.directory?(dir)
    next if ['.', '..', 'obj'].include?(dir)

    Dir.new(dir).each do |file|
        filep = "#{dir}/#{file}"

        next unless File.file?(filep)

        objp = "obj/#{dir}__#{file}.o"

        objs << objp

        next if File.file?(objp) && (File.mtime(objp) > File.mtime(filep))

        case File.extname(filep)
        when '.c'
            exec("#{cc} #{cflags} -c #{filep} -o #{objp}")
        when '.asm'
            exec("#{asm} #{asmflags} #{filep} #{asmout} #{objp} #{asmquiet ? '&> /dev/null' : ''}")
        end
    end
end


exec("#{ar} #{arflags} libc.a #{objs.reject { |o| o[0..9] == 'obj/math__' } * ' '}")
exec("#{ar} #{arflags} libm.a #{objs.select { |o| o[0..9] == 'obj/math__' } * ' '}")
