# Define encoder using function library() and declare dependency of encoder_dep
encoder = library('encoder',
    sources:['HCNode.hpp', 'HCTree.cpp','HCTree.hpp'], 
    dependencies: [bitStream_dep,input_dep,output_dep])

inc = include_directories('.')

encoder_dep = declare_dependency(include_directories: inc,
  link_with: encoder, dependencies: [bitStream_dep,input_dep,output_dep])