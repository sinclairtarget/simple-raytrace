require 'rake/clean'

# Apple application bundle structure is documented here:
# http://tinyurl.com/jz3b9j8

APP_NAME = 'WindowTest'.freeze
SOURCE_DIRECTORY = 'src'.freeze
ASSETS_DIRECTORY = 'assets'.freeze
BUILD_DIRECTORY = 'build'.freeze

APP_DIRECTORY = "#{BUILD_DIRECTORY}/#{APP_NAME}.app".freeze
APP_CONTENTS_DIRECTORY = "#{APP_DIRECTORY}/Contents".freeze
APP_EXECUTABLE_DIRECTORY = "#{APP_CONTENTS_DIRECTORY}/MacOS".freeze
APP_RESOURCES_DIRECTORY = "#{APP_CONTENTS_DIRECTORY}/Resources".freeze

EXECUTABLE_PATH = "#{APP_EXECUTABLE_DIRECTORY}/#{APP_NAME}".freeze

SOURCE_PLIST_PATH = 'Info.plist'.freeze
BUILD_PLIST_PATH = "#{APP_CONTENTS_DIRECTORY}/Info.plist".freeze

SOURCE_FILES = FileList["#{SOURCE_DIRECTORY}/**/*.m",
                        "#{SOURCE_DIRECTORY}/**/*.c"] 
ASSET_FILES = FileList["#{ASSETS_DIRECTORY}/*"]

task :default => [:build_app]

desc 'Builds the entire application, outputting an application bundle.'
task :build_app => [BUILD_PLIST_PATH, EXECUTABLE_PATH, APP_RESOURCES_DIRECTORY]

# TODO: Put object files somewhere separate instead of under /src
file EXECUTABLE_PATH => SOURCE_FILES.ext('.o') do |t|
  mkdir_p t.name.pathmap("%d")
  sh "clang -framework Cocoa -o #{t.name} #{t.prerequisites.join(' ')}"
end
CLEAN.include(SOURCE_FILES.ext('.o'))

file BUILD_PLIST_PATH => SOURCE_PLIST_PATH do |t|
  mkdir_p t.name.pathmap("%d")
  cp SOURCE_PLIST_PATH, BUILD_PLIST_PATH
end

file APP_RESOURCES_DIRECTORY => ASSET_FILES do |t|
  mkdir_p t.name
  cp ASSET_FILES, APP_RESOURCES_DIRECTORY
end

# Uses clang to determine the dependencies of a source file.
# Returns an array of file names.
def file_deps(task_name, file_ext)
  source_file_name = task_name.ext(file_ext)
  return [] unless File.exist?(source_file_name)

  out = `clang -E -MM #{source_file_name}`
  raise "Dependency generation failed!" unless $?.success?

  # Clang dependency file format example:
  # triangle.o: triangle.c triangle.h \
  #   math_utils.h
  out.split(':').last.split
     .reject { |e| e == '\\' || e == source_file_name }
end

rule '.o' => ['.c', *(-> (task_name) { file_deps(task_name, '.c') })] do |t|
  sh "clang -c #{t.source} -o #{t.name}"
end

rule '.o' => ['.m', *(-> (task_name) { file_deps(task_name, '.m') })] do |t|
  sh "clang -fobjc-arc -c #{t.source} -o #{t.name}"
end

CLOBBER.include(BUILD_DIRECTORY)
