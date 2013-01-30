class Console
    @@base   = 0xb8000
    @@width  = 80
    @@height = 25

    @@colors = { black:    0, darkblue:    1, darkgreen: 2, darkcyan: 3,
                 darkred:  4, darkmagenta: 5, brown:     6, gray:     7,
                 darkgray: 8, blue:        9, green:    10, cyan:    11,
                 red:     12, magenta:    13, yellow:   14, white:   15 }


    def initialize
        @x = 0
        @y = 0
        @attr = 7
    end


    def puts(string)
        string.each_char do |chr|
            case chr
            when "\n"
                @y += 1
                @x = 0
            when "\r"
                @x = 0
            else
                pos = @@base + (@y * @@width + @x) * 2

                Memory[pos    ] = chr.asc
                Memory[pos + 1] = @attr

                @x += 1
                if @x >= @@width
                    @x = 0
                    @y += 1
                end
            end

            if @y >= @height
                Memory.memmove(@@base, @@base + @@width * 2, (@@height - 1) * @@width * 2)
                @y -= 1
            end
        end
    end


    def clear
        Memory.memset(@@base, 0, @@width * @@height * 2)
    end


    def set_fg(color)
        @attr = @@colors[color]
    end
end
