# Define output using function library() and declare dependency of output_dep
output = library('output',
    sources:['BitOutputStream.cpp', 'BitOutputStream.hpp'])

inc = include_directories('.')

output_dep = declare_dependency(include_directories: inc,
  link_with: output)