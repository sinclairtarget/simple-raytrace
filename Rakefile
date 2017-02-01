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

SOURCE_FILES = FileList["#{SOURCE_DIRECTORY}/**/*.m"]
ASSET_FILES = FileList["#{ASSETS_DIRECTORY}/*"]

task :default => [:build_app]

desc 'Builds the entire application, outputting an application bundle.'
task :build_app => [BUILD_PLIST_PATH, EXECUTABLE_PATH, APP_RESOURCES_DIRECTORY]

file EXECUTABLE_PATH => SOURCE_FILES.ext('.o') do |t|
  mkdir_p t.name.pathmap("%d")
  sh "clang -framework Cocoa -o #{t.name} #{t.prerequisites.join(' ')}"
end
CLEAN.include(SOURCE_FILES.ext('.o'))

file BUILD_PLIST_PATH do |t|
  mkdir_p t.name.pathmap("%d")
  cp SOURCE_PLIST_PATH, BUILD_PLIST_PATH
end

file APP_RESOURCES_DIRECTORY => ASSET_FILES do |t|
  mkdir_p t.name
  cp ASSET_FILES, APP_RESOURCES_DIRECTORY
end

rule '.o' => ['.m'] do |t|
  sh "clang -c #{t.source} -o #{t.name}"
end

CLOBBER.include(BUILD_DIRECTORY)
