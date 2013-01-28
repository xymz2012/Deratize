#don't profile too early!!!!!!!!!!!!!!!
require 'set'
require "mathn"

class Array
	def row() self[0] end
	def row=(value) self[0] = value end
	def col() self[1] end
	def col=(value) self[1] = value end
end

class Warehouse
	def initialize(path)
		fd =File .new(path, "r")
		@n,@m,@d = fd.readline().chomp.split(" ").map{|x| x.to_i}
		@matrix = fd.readlines().map! do |line|
			line.chomp!
			line.downcase!.split("")
		end
		
		@not_wall = []
		@wall = Set.new
		@mouse = Set.new
		for r in (0...n)
			for c in (0...m)
				pos, val = [r,c], matrix[r][c]
				@not_wall << pos if not val == "x"
				@wall << pos if val == "x"
				@mouse << pos if val == "r"
			end
		end
		
		@template = Set.new
		@d.downto(0) do |dis|
			for c in (0..dis)
				r = dis - c
				@template << [r,c]
				@template << [c,-r]
				@template << [-r,-c]
				@template << [-c,r]
			end
		end
	end
	
	attr_accessor :n
	attr_accessor :m
	attr_accessor :d
	attr_accessor :matrix
	attr_accessor :not_wall
	attr_accessor :wall
	attr_accessor :mouse
	attr_accessor :template
	
	def matrix_at(pos)
		@matrix[pos.row][pos.col]
	end
	
	#one node for astar
	class Node
	def initialize(g,h,d)
			@g = g
			@h = h
			@d = d
		end
		attr_accessor :g
		attr_accessor :h
		attr_accessor :d
	end
	
	#return shortest path(as Array) from sp to ep. return nil if shortest way is no exit
	def AStar(sp, ep, walkable)
		nodes = Hash.new {|hash, key| hash[key] = nil}
		for pos in walkable
			h = (pos.row - ep.row).abs + (pos.col - ep.col).abs
			g = @m * @n
			nodes[pos] = Node .new(g, h, nil)
		end
		
		nodes[sp].g = 0
		open_list = { sp => nodes[sp] }
		close_list = {}
		
		#searching
		until open_list.empty?
			key, node = open_list.min {|a, b| (a[1].g + a[1].h) <=> (b[1].g + b[1].h) }
			open_list.delete(key)
			close_list[key] = node
			
			break if key == ep
			
			#current
			r, c = key
			[[0,1],[0,-1],[1,0],[-1,0]].each do |dr,dc|
				nr, nc, nkey = r+dr, c+dc, [r+dr, c+dc]
				
				#ingnore
				if (not walkable.include?(nkey)) or close_list.has_key?(nkey)
					next
				end
				
				#adjacent 
				next_g, next_d = node.g + 1, [dr, dc]
				next_node  = nodes[nkey]
				
				#already in openlist
				if open_list.has_key?(nkey)
					if next_g < next_node.g
						next_node.g = next_g
						next_node.d = next_d
					end
				end
				
				#not in openlist
				if not open_list.has_key?(nkey)
					next_node.g = next_g
					next_node.d = next_d
					open_list[nkey] = next_node
				end
			end
		end
		
		# no shortest path
		return nil if not close_list.include?(ep)

		# find shortest path
		pos, node = Array.new(ep) , close_list[ep]
		ret = []
		loop do
			ret << Array.new(pos)
			break if pos == sp
			pos.col -= node.d.col
			pos.row -= node.d.row
			node = nodes[pos]
		end
		return ret.reverse!
	end
	
	#put a bomb explosion on position pos and regardless of wall. return explosion range as a set
	def exposion_range_without_wall(pos)
		range = Set.new
		@template.each do |orig_pos|
			trans_pos = Array.new(orig_pos)
			trans_pos.row += pos.row
			trans_pos.col += pos.col
			if (0...n).cover?(trans_pos.row) and (0...m).cover?(trans_pos.col)
				range << trans_pos
			end
		end
		return range
	end
	
	#put a bomb explosion on position pos. return explosion range as a set
	def explosion_range(bomb_pos)
		candidate = exposion_range_without_wall(bomb_pos) - @wall
		elect = Set.new
		walkable = Set.new(candidate)
		
		loop do
			break if candidate.empty?
			s, e = bomb_pos, candidate.first
			
			path = AStar(s, e, walkable)
			
			#no shortest path
			if not path
				candidate.delete(s)
				candidate.delete(e)
				elect << s
				next
			end
			
			#find shortest path
			path.each_index do |step|
				pos = path[step]
				candidate.delete(pos)
				elect << pos if step <= @d   # bomb on bom_pos can reach pos
			end
		end
		return elect
	end
	
end

def main
	wh = Warehouse .new("../input3.txt")
	
	all = []
	
	for mice in wh.mouse
		all << wh.explosion_range(mice)
	end
	
	all_index = (0...all.length)

	for i in (0...wh.not_wall.length)
		bomb1 = wh.not_wall[i]
		ms_on_bomb1 = all.select{|mouse| mouse.include?(bomb1)}
		ms_on_bomb2 = all.select{|mouse| not mouse.include?(bomb1)}
		for j in (i+1...wh.not_wall.size)
			cover = true
			bomb2 = wh.not_wall[j]
			ms_on_bomb2.each do |mouse|
				cover = false if not mouse.include?(bomb2)
			end
			print [bomb1,bomb2], "\n" if cover
		end
	end
	print "-1"
end

main()
