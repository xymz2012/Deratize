#don't profile too early!!!!!!!!!!!!!!!
require 'set'

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
		@mouse = Set.new
		for r in (0...n)
			for c in (0...m)
				pos, val = [r,c], matrix[r][c]
				@not_wall << pos if not val == "x"
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
	
	def matrix_at(pos)
		@matrix[pos.row][pos.col]
	end
	
	#return shortest path(as Array) from s to a. return [s] if shortest way is no exit
	def AStar(s, e)
		return [s,e]
	end
	
	#put a bomb explosion on position pos and regardless of wall. return explosion range as a set
	def exposion_range_without_wall(pos)
		range = Set.new
		@template.each do |orig_pos|
			trans_pos = Array.new(orig_pos)
			trans_pos.row += pos.row
			trans_pos.col += pos.col
			range << trans_pos
		end
		return range
	end
	
	#put a bomb explosion on position pos. return explosion range as a set
	def explosion_range(bomb_pos)
		candidate = exposion_range_without_wall(bomb_pos)
		elect = Set.new
		
		loop do
			break if candidate.empty?
			s, e = bomb_pos, candidate.first
			
			path = AStar(s, e)
			
			path.each_index do |step|
				pos = path[step]
				candidate.delete(step)
				elect << pos if index <= @d   # bomb on bom_pos can reach pos
			end
		end
		return elect
	end
	
	
	attr_accessor :n
	attr_accessor :m
	attr_accessor :d
	attr_accessor :matrix
	attr_accessor :not_wall
	attr_accessor :mouse
	attr_accessor :template
end

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
	


=begin
	A* algorithm. sp is start position. ep_set is a set of end positions. wh 
describes the whole warehouse.
	return a set of positions those start position can reach by not larger than wh.d steps.
=end
def AStar(sp, ep_set, wh)
	nodes = Array.new(wh.n) do |r|
		Array.new(wh.m) do |c|
			h = ([r, wh.n-r].max - 1) * ([c, wh.m-c].max - 1) - 1
			Node.new(wh.m * wh.n, h, nil)
		end
	end
	
	nodes[sp.row][sp.col].g = 0
	open_list = { sp => nodes[sp.row][sp.col] }
	close_list = {}
	
	#reachable positions
	reach_set = Set.new
	
	until open_list.empty?
		key, node = open_list.min {|a, b| (a[1].g + a[1].h) <=> (b[1].g + b[1].h) }
		open_list.delete(key)
		
		# a new close node
		close_list[key] = node
		if ep_set.delete?(key)
			reach_set << key if node.g <= wh.d # add if reachable
			break if ep_set.empty? # break if find all the path to end position
		end
		
		r, c = key
		[[0,1],[0,-1],[1,0],[-1,0]].each do |dr,dc|
			nr, nc, nkey = r+dr, c+dc, [r+dr, c+dc]
			
			#ingnore if nkey is wall or nkey is already in closelist
			if wh.matrix[nr][nc] == "x" or close_list.has_key?(nkey)
				next
			end
			
			#adjacent node
			next_g, next_d = node.g + 1, [dr, dc]
			next_node  = nodes[nr][nc]
			
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
	
	return reach_set
end


def main
	wh = Warehouse .new("../input2.txt")
	
	all = []
	
	for mice in wh.mouse
		all << wh.explosion_range(mice)
	end
	
end

main()
