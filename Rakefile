SOURCE_DIRECTORY = 'src'.freeze
BUILD_DIRECTORY = 'build'.freeze

task :default => [:build]

task :build => ['run']

file 'run' => Dir["#{SOURCE_DIRECTORY}/*.m"] do |t|
  sh "clang -framework Cocoa -o #{t.name} #{t.prerequisites.join(' ')}"
end

rule '.o' => ['.m'] do |t|
  sh "clang -c #{t.source} -o #{t.name}"
end

task :clean do
  sh "rm -rf run *.o"
end
