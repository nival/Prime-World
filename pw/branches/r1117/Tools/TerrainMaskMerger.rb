#!ruby -w

require 'ftools'

##
## Command line: bin-files with local/global layers in 
## correct order, e.g.:
##
## script.rb PF.local_layer_mask.bin PF.global_layer_0.bin PF.global_layer_1.bin
##

maxsize = 0
layers = Array.new
ARGV.each do |fname|
  membuf = IO.read(fname)
  pixels = membuf.unpack('C*')
  maxsize = [maxsize, pixels.length].max
  layers << pixels
end

result = Array.new
maxsize.times do |i|
  slice = Array.new
  layers.each_with_index do |pixels, id|
    slice << (id + 1) if pixels.shift == 255
  end
  case slice.length
    when 1
      result << slice.pop
    when 0
      result << 1
    else
      result << slice.pop
      puts 'WARNING: Several layers have nonzero value at ' + i.to_s
  end
end

File.open('merged.bin', 'w') do |f|
  f.write(result.pack('C*'))
end


ARGV.each do |fname|
  File.copy('merged.bin', fname)
end
