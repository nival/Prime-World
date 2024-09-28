#!ruby -w

require 'optparse'
require 'pp'

dumpall = false
flatmode = false
immmode = false
nostl = false
nolines = false
category = 'unfreed'
arysort = proc {|a,b| a.file <=> b.file}

opts = OptionParser.new(nil, 20) do |opts|
  opts.on('-a', '--all', 
    'Output all allocations. By default only unfreed',
    'allocations are processed') do
    dumpall = true
	category = 'allocated'
  end

  opts.on('-f', '--flat', 
    'Flat mode output, shows how many allocation requests',
    'go through the file/line. By default callstack tree',
    'is displayed.') do
    flatmode = true
  end

  opts.on('-i', '--immediate', 
    'Immediate stack frame output for Flat Mode, shows only',
    'the deepest stack entry. By default is off') do
    immmode = true
  end

  opts.on('-n', '--no-stl', 
    'Drop nstl calls from stack.') do
    nostl = true
  end

  opts.on('-l', '--no-lines', 
    'Drop line numbers from stack entries.') do
    nolines = true
  end

  sort_types = [:file, :count, :size]
  opts.on('-s', '--sort [SORT]', sort_types,
    'Parameter to sort by in flat mode (file, count, size).') do |st|
    arysort = proc {|a,b| a.method(st).call <=> b.method(st).call}
  end

  opts.on_tail("-h", "--help", "Show this message.") do
    puts opts
    exit
  end
end

opts.parse!(ARGV)

filename = nil
if !ARGV.empty?
	filename = ARGV.first
else
	filename = `dir /b /s /o-d ..\\Bin\\log\\*-performance.txt`.split.first
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
      child = a.find {|c| c.kind_of?(Tree) and c.value == e}
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
    @children.sort.each_with_index do |e,i| 
    	if e.kind_of?(Tree)
    		e.print_tree_internal(indent + addon, i == ilast ? '  ' : '| ')
    	else
    		puts indent + addon + '+-' + e.to_s
    	end
    end
  end

  def <=>(other)
    case other
      when Tree
	    @value <=> other.value
	  when Counter
	    -1
	  else
	    0
	end
  end
end

class Event
	attr_reader :id, :size, :addr, :stack
	attr_writer :stack
	def initialize(id, size, addr)
		@id = id
		@size = size
		@addr = addr
		@stack = Array.new
		@freed = false
	end

	def to_s
		id
	end
end

class Counter
	attr_reader :name, :values

	def initialize(name, event)
		@name = name
		@values = Array.new(1, event.id)
	end

	def add(event)
		@values.push(event.id)
	end

	def to_s
		"<#{@name.upcase}:#{@values.length}> = [#{@values.join(', ')}]"
	end

	def <=>(other)
	  case other
	  	when Counter
	      @name <=> other.name
	    when Tree
	      1
	    else
	      0
	  end
	end
end

class Total
	attr_reader :file, :count, :size, :sizemin, :sizemax

	def initialize(file)
	  @file = file
	  @count = 0
	  @size = 0
	  @sizemin = 2000000000
	  @sizemax = 0
	end

	def add(size)
	  @size += size
	  @sizemin = size if @sizemin > size
	  @sizemax = size if @sizemax < size
	  @count += 1
	end

	def to_s
	  if sizemin != sizemax
		  "%-50s %4i times %6i bytes total (%i..%i)" % [file, count, size, sizemin, sizemax]
	  else
		  "%-50s %4i times %6i bytes total (%i)" % [file, count, size, sizemin]
	  end
	end
end

types = Hash.new
event = nil
File.open(filename) do |f|
	f.readlines.each do |line|
		line.chomp!
		next if line =~ %r"newdelete"
		next if nostl && (line.include?('nvector.h') || line.include?('nstring.h') || line.include?('nlist.h') || line.include?('nqueue.h') || line.include?('system\nhash'))
		line = $1 if line =~ %r"^\d/\d \d\d:\d\d:\d\d\.\d\d (.*)"
		case line
			when %r"^\[(\d+)\]: allocated (\d+) bytes at (0x[0-9A-F]+):"
				types[category] = Array.new unless types[category]
				event = Event.new($1, $2, $3)
				types[category].push(event)
			when %r"^\[(\d+)\]: freed"
				if !dumpall and types[category]
					types[category].delete_if {|e| e.id == $1}
				end
			when %r"src\\((.+)\(\d+\))"
				topush = nolines ? $2 : $1
				event.stack.push(topush) if event.stack.empty? or event.stack.last != topush
		end
	end
end

if !flatmode
	total = 0
	root = Tree.new(category.upcase + ' in ' + filename)
	types.each do |type, events|
		total = total + events.length
		events.each do |event|
			children = root.add_list(event.stack.reverse)
			counter = children.find {|c| c.kind_of?(Counter) and c.name == type}
			if counter == nil
				children.push(Counter.new(type, event))
			else
				counter.add(event)
			end
		end
	end
	root.value = total.to_s + ' ' + root.value
	root.print_tree
else
	hash = Hash.new
	types.each do |type, events|
		events.each do |event|
			if immmode
			  next if event.stack.empty?
			  event.stack = [event.stack.first]
			end
  			event.stack.each do |line|
  				hash[line] = [] unless hash.include?(line)
  				hash[line] << event
  			end
		end
	end
	ary = Array.new
	hash.sort.each do |line, events|
		line += ':'
		total = Total.new(line)
		events.each { |e| total.add(e.size.to_i) }
		ary << total
	end
	puts ary.sort(&arysort).join("\n")
end

