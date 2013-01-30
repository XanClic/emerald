# coding: utf-8
# Patches the float class.

class Float
    def >>(amount)
        # genius.png
        (self / 2.0**amount).truncate
    end
end
