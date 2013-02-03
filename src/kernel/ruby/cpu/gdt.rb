# coding: utf-8
# GDT stuff.

SLC_SYS_CODE = 0x08
SLC_SYS_DATA = 0x10


class GDT < XDT
    def load(code, data)
        X86.lgdt(@xdtr, code, data)
    end


    def self.init
        $gdt = GDT.new(5)

        [ :sys_np, :sys_rx, :sys_rw, :usr_rx, :usr_rw ].each_indexed_value do |i, access|
            $gdt[i].type  = access
            $gdt[i].flags = [:size]
            $gdt[i].base  = 0x00000000
            $gdt[i].limit = 0xffffffff
        end

        $gdt.load(SLC_SYS_CODE, SLC_SYS_DATA)
    end
end
