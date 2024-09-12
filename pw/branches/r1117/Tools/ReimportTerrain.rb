#!ruby -w

dirname, root = ['..\Data\Terrain\Elements', '..\Data'].collect { |dir| File.expand_path(dir) }
root = Regexp.new(root + '/')

result = Array.new
Dir.foreach(dirname) do |name|
  if name =~ %r".stat.xdb"i
    path = File.join(dirname, name)
    result << path.sub(root, '')
  end
end

system("cd ..\\Bin && ..\\Src\\_Debug\\PF_EditorC.exe import --fast #{result.join(' ')}")
