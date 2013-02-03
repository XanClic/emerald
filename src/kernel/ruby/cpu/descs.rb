# coding: utf-8
# [GIL]DT descriptors.

class XDTDesc
    @@gen_struct = RStruct.new({
        type: [5, :u8]
    })

    @@type_hash = {
        sys_np:   0x10, # not present
        sys_rx:   0x9A, # readable/executable
        sys_rw:   0x92, # readable/writable
        sys_r:    0x90, # readable
        sys_x:    0x98, # executable
        usr_rx:   0xFA,
        usr_rw:   0xF2,
        usr_r:    0xF0,
        usr_x:    0xF8,

        sys_task: 0x8D,
        sys_intr: 0x8E,
        sys_trap: 0x8F,
        usr_task: 0xED,
        usr_intr: 0xEE,
        usr_trap: 0xEF
    }


    def self.get(base, index)
        desc = @@gen_struct.instance(base + index * 8)

        if (desc.type & (1 << 4)) != 0
            return XDTDescSegment.new(base, index)
        else
            return XDTDescGate.new(base, index)
        end
    end


    def type
        @desc.type
    end


    def type=(val)
        if val.kind_of?(Symbol)
            val = @@type_hash[val]
        end

        @desc.type = val
    end
end


class XDTDescSegment < XDTDesc
    @@desc_struct = RStruct.new({
        limit_lo: [0, :u16],
        base_lo:  [2, :u16],
        base_mi:  [4, :u8],
        type:     [5, :u8],
        limit_hi: [6, :u8],
        base_hi:  [7, :u8]
    })

    @@flag_bits = { available: 0x10, long_mode: 0x20, size: 0x40, granularity: 0x80 }


    def initialize(base, index)
        @desc = @@desc_struct.instance(base + index * @@desc_struct.size)
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
end


class XDTDescGate < XDTDesc
    @@desc_struct = RStruct.new({
        offset_lo: [0, :u16],
        selector:  [2, :u16],
        type:      [5, :u8],
        offset_hi: [6, :u16]
    })


    def initialize(base, index)
        @desc = @@desc_struct.instance(base + index * 8)
    end


    def base
        @desc.offset_lo | (@desc.offset_hi << 16)
    end


    def selector
        @desc.selector
    end


    def base=(addr)
        @desc.offset_lo = addr & 0xFFFF
        @desc.offset_hi = addr >> 16
    end


    def selector=(sel)
        @desc.selector = sel
    end
end
