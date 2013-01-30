# coding: utf-8
# GDT stuff.

class GDTDesc
    @@flag_bits = { available: 0x10, long_mode: 0x20, size: 0x40, granularity: 0x80 }

    @@access_hash = {
        sys_np: 0x00, # not present
        sys_rx: 0x9A, # readable/executable
        sys_rw: 0x92, # readable/writable
        sys_r:  0x90, # readable
        sys_x:  0x98, # executable
        usr_rx: 0xFA,
        usr_rw: 0xF2,
        usr_r:  0xF0,
        usr_x:  0xF8
    }


    def initialize(desc)
        @desc = desc
    end


    def limit
        if flags[:granularity]
            return ((@desc.limit_lo | ((@desc.limit_hi & 0xF) << 16)) << 12) | 0xFFF
        else
            return   @desc.limit_lo | ((@desc.limit_hi & 0xF) << 16)
        end
    end


    def base
        @desc.base_lo | (@desc.base_mi << 16) | (@desc.base_hi << 24)
    end


    def flags
        return @@flag_bits.keys.select { |flag| (@desc.limit_hi & @@flag_bits[flag]) != 0 }
    end


    def access
        @desc.type
    end


    def limit=(lim)
        if lim >= 1048576
            self.flags += [:granularity]
            lim >>= 12
        else
            self.flags -= [:granularity]
        end

        @desc.limit_lo = lim & 0xFFFF
        @desc.limit_hi = (@desc.limit_hi & 0xF0) | (lim >> 16)
    end


    def base=(addr)
        @desc.base_lo = addr & 0xFFFF
        @desc.base_mi = (addr >> 16) & 0xFF
        @desc.base_hi = addr >> 24
    end


    def flags=(flg)
        val = @desc.limit_hi & 0xF

        (@@flag_bits.keys & flg).each do |flag|
            val |= @@flag_bits[flag]
        end

        @desc.limit_hi = val
    end


    def access=(val)
        if val.kind_of?(Symbol)
            val = @@access_hash[val]
        end

        @desc.type = val
    end
end


class GDT
    def initialize(descs)
        @desc = RStruct.new({
            limit_lo: [0, :u16],
            base_lo:  [2, :u16],
            base_mi:  [4, :u8],
            type:     [5, :u8],
            limit_hi: [6, :u8],
            base_hi:  [7, :u8]
        })

        @desc_count = descs
        @base       = malloc(descs * @desc.size)


        gdtr_struct = RStruct.new({ limit: [0, :u16], base: [2, :u32] })

        @gdtr = malloc(gdtr_struct.size)

        gdtr_instance = gdtr_struct.instance(@gdtr)

        gdtr_instance.limit = descs * @desc.size - 1
        gdtr_instance.base  = @base
    end


    def [](i)
        return GDTDesc.new(@desc.instance(@base + i * @desc.size))
    end


    def load(code, data)
        X86.lgdt(@gdtr, code, data)
    end
end


def build_gdt
    $gdt = GDT.new(5)

    [ :sys_np, :sys_rx, :sys_rw, :usr_rx, :usr_rw ].each_indexed_value do |i, access|
        $gdt[i].access = access
        $gdt[i].flags  = [:size]
        $gdt[i].base   = 0x00000000
        $gdt[i].limit  = 0xffffffff
    end

    $gdt.load(0x08, 0x10)
end
