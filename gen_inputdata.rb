n, m, d = 1000, 1000, 8
x, r = 5, 2 # x/10000, r/10000

x_range = (0...x)
r_range = (x...x+r)

fd = File.new("input.txt", "w")

fd.puts "%i %i %i"%[n, m, d]
fd.puts "X"*m

for i in (1...n-1)
	line = 'X'
	for j in (1...m-1)
		rrr = rand(10000)
		if x_range.include?(rrr)
			line += "X"
			next
		elsif r_range.include?(rrr)
			line += "R"
			next
		else
			line += "."
		end
		
	end
	line += 'X'
	fd.puts line
end

fd.puts "X"*m
fd.close
