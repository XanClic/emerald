# coding: utf-8
# Raw memory structures

class RStructInst
    def initialize(struct, base)
        @struct = struct
        @addr   = base

        struct.each do |member|
            RStructInst.define_method(member) { self[member] }
            RStructInst.define_method("#{member.to_s}=".intern) { |val| self[member] = val }
        end
    end


    def [](member)
        field = @struct[member]

        case field[1]
        when :u8
            return Memory8[@addr + field[0]]
        when :u16
            return Memory16[@addr + field[0]]
        when :u32
            return Memory32[@addr + field[0]]
        when :u64
            return Memory64[@addr + field[0]]
        else
            raise "Unknown type #{field[1].to_s} in struct."
        end
    end


    def []=(member, value)
        field = @struct[member]

        case field[1]
        when :u8
            Memory8[@addr + field[0]] = value
        when :u16
            Memory16[@addr + field[0]] = value
        when :u32
            Memory32[@addr + field[0]] = value
        when :u64
            Memory64[@addr + field[0]] = value
        else
            raise "Unknown type #{field[1].to_s} in struct."
        end
    end
end


class RStruct
    def initialize(structure)
        @struct = structure

        @size = 0
        @struct.each_value do |val|
            member_end = val[0] + { u8: 1, u16: 2, u32: 4, u64: 8 }[val[1]]

            @size = member_end if member_end > @size
        end
    end


    def [](member)
        @struct[member]
    end


    def each
        @struct.each_key do |name|
            yield name
        end
    end


    def instance(address)
        return RStructInst.new(self, address)
    end


    def size
        @size
    end

    alias_method :length, :size
end
