# coding: utf-8
# GDT stuff.

class GDT < XDT
    def load(code, data)
        X86.lgdt(@xdtr, code, data)
    end
end


def build_gdt
    $gdt = GDT.new(5)

    [ :sys_np, :sys_rx, :sys_rw, :usr_rx, :usr_rw ].each_indexed_value do |i, access|
        $gdt[i].type  = access
        $gdt[i].flags = [:size]
        $gdt[i].base  = 0x00000000
        $gdt[i].limit = 0xffffffff
    end

    $gdt.load(0x08, 0x10)
end
