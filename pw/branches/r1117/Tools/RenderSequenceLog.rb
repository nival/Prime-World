#!ruby -wn

BEGIN {
  class Counter
    attr_reader :count, :level

    def initialize(count, level)
      @count = count
      @level = level
    end

    def next
      Counter.new(@count + 1, @level)
    end

    def <=>(other)
      [@count, @level] <=> [other.count, other.level]
    end

    def to_i
      @count
    end

    def to_s
      ' ' * @level * 4 + @count.to_s.rjust(4)
    end
  end

  $dirs = Hash.new(Counter.new(0,0))
  $files = Hash.new(Counter.new(0,1))
  $uids = Hash.new(Counter.new(0,2))
  $type = Hash.new
  $material = Hash.new

  $subtotal = 0
  $total = 0
}

line = $_[18..-1]
if line =~ /^class/
  klass, uid, material, mid = line.split(/;\s+/)
  file = uid.split(/:/).first
  dir = file == "(unknown)" ? file : File.dirname(file)
  $dirs[dir] = $dirs[dir].next
  $files[file] = $files[file].next
  $uids[uid] = $uids[uid].next
  $type[uid] = klass
  $material[uid] = material + "[#{mid}]"
  $subtotal = $subtotal + 1
else
  puts $subtotal.to_s.rjust(4) + ' - Subtotal' if $subtotal > 0
  total = $dirs.to_a + $files.to_a + $uids.to_a
  total.sort.each do |pair|
    name, count = pair
    addon = $type[name] ? ' (' + $type[name] + '; ' + $material[name] + ')' : ''
    puts count.to_s + ' - ' + name + addon
  end
  $dirs.clear
  $files.clear
  $uids.clear
  $total = $total + $subtotal
  $subtotal = 0
  puts line
end

END {
  puts $total.to_s.rjust(4) + ' - Total'
}
