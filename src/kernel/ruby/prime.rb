# coding: utf-8

# Primordial functions, e.g. for handling C fopen (when mruby tries to execute
# load).


def fopen(fname, mode)
    pos = 0xb8000
    fname.each_char do |f|
        Memory[pos    ] = Helper.asc(f)
        Memory[pos + 1] = 15
        pos += 1
    end
end
