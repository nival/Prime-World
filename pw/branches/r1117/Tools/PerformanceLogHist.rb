#!ruby -w

filename = nil
if !ARGV.empty?
	filename = ARGV.first
else
	filename = `dir /b /s /o-d ..\\Bin\\log\\*-performance.txt`.split.first
	raise 'No logs found.' if !filename
end

sizes = Hash.new
File.open(filename) do |f|
	f.readlines.each do |line|
		line.chomp!
		if line =~ %r"^\[(\d+)\]: allocated (\d+) bytes at (0x[0-9A-F]+):"
		  size = $2.to_i
		  sizes[size] = (sizes[size] || 0) + 1
		end
	end
end

sizes.keys.sort.each do |size|
  puts "#{size}, #{sizes[size]}"
end
