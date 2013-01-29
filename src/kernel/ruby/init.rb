# coding: utf-8
# Support for loading ruby source files

def mboot_find(file)
    0.upto($mboot_mod_count - 1) do |i|
        ofs = $mboot_mod_addr + i * 16

        if Memory.cstr(Memory32[ofs + 8]) == file
            return [Memory32[ofs], Memory32[ofs + 4] - Memory32[ofs]]
        end
        Helper.load(Memory32[ofs], Memory32[ofs + 4] - Memory32[ofs])
    end

    return nil
end


def init_mboot()
    if !(Memory32[MBOOT] & (1 << 3))
        raise 'No multiboot modules given'
    end

    $mboot_mod_count = Memory32[MBOOT + 20]
    $mboot_mod_addr  = Memory32[MBOOT + 24]
end



init_mboot()



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
