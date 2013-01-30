# coding: utf-8
# Patches the string class.

class String
    alias_method :top_asc, :asc

    def asc
        top_asc(self)
    end

    def %(arr)
        sprintf(self, *arr)
    end
end
