subdir('input')
subdir('output')

bitStream = library('bitStream')

inc = include_directories('input','output')

bitStream_dep = declare_dependency(include_directories: inc,
  link_with: bitStream)