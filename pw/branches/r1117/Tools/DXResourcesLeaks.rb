#!ruby -w

filename = ''
if !ARGV.empty?
	filename = ARGV.first
else
	filename = `dir /b /s /o-d ..\\Bin\\DXResourcesLeaks*.log`.split.first
	raise 'No logs found.' if !filename
end

class Tree
  attr_accessor :value, :children

  def initialize(value = nil, children = Array.new)
    children.kind_of?(Array) or raise "Tree children must be in Array"
    @value = value
    @children = children
  end

  def inspect
    if @children.empty?
      '(' + @value.inspect + ')'
    else
      '(' + @value.inspect + ', ' + @children.inspect + ')'
    end
  end

  def add_list(elements)
    elements.kind_of?(Array) or raise "Elements must be an Array"
    a = @children
    elements.each do |e|
      child = a.find {|c| c.value == e}
      if child == nil
        child = Tree.new(e)
        a.push child
      end
      a = child.children
    end
    a
  end

  def print_tree
    print_tree_internal('', '  ')
  end

  def print_tree_internal(indent, addon)
    puts indent + '+-' + @value.to_s
    ilast = @children.length - 1
    @children.each_with_index do |e,i| 
    	if e.kind_of?(Tree)
    		e.print_tree_internal(indent + addon, i == ilast ? '  ' : '| ')
    	else
    		puts indent + addon + '+-' + e.to_s
    	end
    end
  end
end

class Counter
	attr_reader :name, :value

	def initialize(name)
		@name = name
		@value = 1
	end

	def inc
		@value = @value + 1
	end

	def to_s
		"<#{@name.upcase}:#{@value}>"
	end
end

types = Hash.new
stack = nil
File.open(filename) do |f|
	f.readlines.each do |line|
		line.chomp!
		next if line =~ %r"dxutils\.cpp\(\d+\)"
		case line
			when %r"^\d+\. (.+):"
				types[$1] = Array.new unless types[$1]
				stack = Array.new
				types[$1].push(stack)
			when %r"pf\\src\\(\w+\\.+\(\d+\))"
				stack.push($1)
		end
	end
end

total = 0
root = Tree.new(' LEAKS in ' + filename)
types.each do |type, stacks|
	total = total + stacks.length
	stacks.each do |stack|
		children = root.add_list(stack.reverse)
		child = children.find {|c| c.name == type}
		if child == nil
			children.push(Counter.new(type))
		else
			child.inc
		end
	end
end

root.value = total.to_s + root.value
root.print_tree
