require 'rake/clean'

APP_NAME = 'Test'.freeze
SOURCE_DIRECTORY = 'src'.freeze
BUILD_DIRECTORY = 'build'.freeze

APP_DIRECTORY = "#{BUILD_DIRECTORY}/#{APP_NAME}.app"
APP_CONTENTS_DIRECTORY = "#{APP_DIRECTORY}/Contents"
APP_EXECUTABLE_DIRECTORY = "#{APP_CONTENTS_DIRECTORY}/MacOS"
EXECUTABLE_PATH = "#{APP_EXECUTABLE_DIRECTORY}/#{APP_NAME}"

SOURCE_FILES = FileList["#{SOURCE_DIRECTORY}/**/*.m"]

task :default => [:build_app]

desc 'Builds the entire application, outputting an application bundle.'
task :build_app => [EXECUTABLE_PATH]

file EXECUTABLE_PATH => SOURCE_FILES.ext('.o') do |t|
  mkdir_p t.name.pathmap("%d")
  sh "clang -framework Cocoa -o #{t.name} #{t.prerequisites.join(' ')}"
end
CLEAN.include(SOURCE_FILES.ext('.o'))
CLOBBER.include(BUILD_DIRECTORY)

rule '.o' => ['.m'] do |t|
  sh "clang -c #{t.source} -o #{t.name}"
end
