#  Define compress_exe and uncompress_exe to output executable file named 
#  compress.cpp.executable and uncompress.cpp.executable
subdir('bitStream')
subdir('encoder')
# src = library('src',
#     sources:['compress.cpp', 'FileUtils.hpp','uncompress.cpp'],
#     dependencies: [bitStream_dep, encoder_dep])
     
inc = include_directories('.')

# src_dep = declare_dependency(include_directories: inc,
#     link_with: src, dependencies: [bitStream_dep, input_dep, output_dep, encoder_dep])

compress_exe = executable('compress.cpp.executable',
    sources: ['compress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep],
    install : true)

uncompress_exe = executable('uncompress.cpp.executable',
    sources: ['uncompress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep],
    install : true)


