# coding: utf-8
# Patches the array class.

class Array
    def &(other_array)
        return select { |x| other_array.include?(x) }
    end

    def each_indexed_value
        self.each_index do |i|
            yield i, self[i]
        end
    end
end
