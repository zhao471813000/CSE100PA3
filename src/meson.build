#  Define compress_exe and uncompress_exe to output executable file named 
#  compress.cpp.executable and uncompress.cpp.executable
subdir('bitStream')
subdir('encoder')


compress_exe = executable('compress.cpp.executable',
    sources: ['compress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep, cxxopts_dep],
    install : true)

uncompress_exe = executable('uncompress.cpp.executable',
    sources: ['uncompress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep, cxxopts_dep],
    install : true)


