# coding: utf-8
# Support for loading ruby source files and all the initialization stuff

class Tar
    def initialize(address)
        @base = address
    end

    def each
        addr = @base

        while Memory8[addr] != 0
            name = Memory.cstr(addr) # FIXME

            size = 0
            (0..10).each do |pos|
                size = (size << 3) + Memory8[addr + 124 + pos] - 48
            end

            yield name, addr + 512, size

            addr += 512 + ((size + 511) & ~511)
        end
    end
end


class Multiboot
    def initialize(address)
        @base = address

        @mboot_mod_count = Memory32[@base + 20]
        @mboot_mod_addr  = Memory32[@base + 24]

        if ((Memory32[@base] & (1 << 3)) == 0) || (@mboot_mod_count == 0)
            raise 'No multiboot modules given'
        end

        @tar = Tar.new(Memory32[@mboot_mod_addr])
    end

    def tar
        @tar
    end
end


def load_file_find(file)
    $mboot.tar.each do |name, addr, size|
        return [addr, size] if name == file
    end

    return nil
end



$mboot = Multiboot.new(MBOOT)



load 'patches/array.rb'
load 'patches/float.rb'
load 'patches/string.rb'

load 'helpers/struct.rb'

load 'cpu/descs.rb'
load 'cpu/desc_tables.rb'
load 'cpu/gdt.rb'
load 'cpu/idt.rb'

load 'drivers/console.rb'



out = Console.new

out.clear
out.set_fg(:darkgreen)
out.puts('Emerald')
out.set_fg(:gray)
out.puts(" reporting in!\nRunning on ")
out.set_fg(:darkred)
out.puts('mruby')
out.set_fg(:gray)
out.puts(".\n\n")


class Console
    def status(msg)
        puts('%-70s' % msg)
    end

    def status_completion(msg, color)
        set_fg(:blue); puts('[')
        set_fg(color); puts(msg)
        set_fg(:blue); puts(']')
        set_fg(:gray); puts("\n")
    end

    def done
        status_completion(' DONE ', :white)
    end

    def failed
        status_completion(' FAIL ', :red)
    end
end


out.status('Changing to custom GDT...')

build_gdt()

out.done


out.status('Loading IDT...')

build_idt()

out.done
