# coding: utf-8
# Support for loading ruby source files

class Tar
    def initialize(address)
        @base = address
    end

    def each
        addr = @base

        while Memory8[addr] != 0
            name = Memory.cstr(addr) # FIXME

            size = 0
            (0..11).each do |pos|
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
        give name
        return [addr, size] if name == file
    end

    return nil
end



$mboot = Multiboot.new(MBOOT)



load 'console.rb'


out = Console.new

out.clear
out.set_fg(:darkgreen)
out.puts("Emerald")
out.set_fg(:gray)
out.puts(" reporting in!\nRunning on ")
out.set_fg(:darkred)
out.puts("mruby")
out.set_fg(:gray)
out.puts(".\n")
