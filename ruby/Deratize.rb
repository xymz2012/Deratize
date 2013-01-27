#don't profile too early!!!!!!!!!!!!!!!
require 'set'
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
	end
	attr_accessor :n
	attr_accessor :m
	attr_accessor :d
	attr_accessor :matrix
	attr_accessor :not_wall
	attr_accessor :mouse
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
	
class Array
	def row() self[0] end
	def col() self[1] end
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
		if key == [1,5]
			break
		end
		#if ep_set.delete?(key)
		#	reach_set << key if node.g <= wh.d # add if reachable
		#	break if ep_set.empty? # break if find all the path to end position
		#end
		
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
	
	bomb_seq = []
	
	for bomb_pos in wh.not_wall
		ep_set = Set.new(wh.mouse)
		bomb_seq << [bomb_pos , AStar(bomb_pos, ep_set, wh)]
	end
	
	find = false
	for i in (0...bomb_seq.length)
		if bomb_seq[i][0] == [1,2] 
			p bomb_seq[i][1]
		end
		if bomb_seq[i][0] == [5,8]
			p bomb_seq[i][1]
		end
	end
	
	for i in (0...bomb_seq.length)
		for j in (i+1...bomb_seq.length)
			if bomb_seq[i][1] + bomb_seq[j][1] == wh.mouse
				r1, c1, r2, c2 = bomb_seq[i][0].row + 1, bomb_seq[i][0].col + 1,bomb_seq[j][0].row + 1, bomb_seq[j][0].col + 1
				print [r1, c1, r2, c2],"\n"
				find = true
			end
		end
	end
	print -1, "\n" if not find
end

main()

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

def problem83
	matrix = File.readlines("matrix.txt").map do |line| 
		line.chomp.split(",").map{|x| x.to_i}
	end
	
	len = matrix.size
	minval = matrix.map{|line| line.min}.min
	maxval = matrix.map{|line| line.max}.max
		
	nodes = Array.new(len) do |r|
		Array.new(len) do |c|
			maxg = maxval * len * len
			h = (len * 2 - r - c - 1) * minval
			Node.new(maxg, h, nil)
		end
	end
	
	nodes[0][0].g = matrix[0][0]
	openlist = { [0, 0] => nodes[0][0]}
	closelist = {}
	walkable = (0...len)
		
	#finding
	until openlist.empty?
		key, node = openlist.min {|a, b| (a[1].g + a[1].h) <=> (b[1].g + b[1].h) }
		openlist.delete(key)
		closelist[key] = node
			
		break if key == [len-1,len-1]
			
		#current
		r, c = key
		[[0,1],[0,-1],[1,0],[-1,0]].each do |dr,dc|
			nr, nc, nkey = r+dr, c+dc, [r+dr, c+dc]
				
			#ingnore
			if not walkable.include?(nr) or not walkable.include?(nc) or closelist.has_key?(nkey)
				next
			end
				
			#adjacent 
			next_g, next_d = node.g + matrix[nr][nc], [dr, dc]
			next_node  = nodes[nr][nc]
				
			#already in openlist
			if openlist.has_key?(nkey)
				if next_g < next_node.g
					next_node.g = next_g
					next_node.d = next_d
				end
			end
				
			#not in openlist
			if not openlist.has_key?(nkey)
				next_node.g = next_g
				next_node.d = next_d
				openlist[nkey] = next_node
			end
		end
	end
		
	closelist[[len-1,len-1]].g
end