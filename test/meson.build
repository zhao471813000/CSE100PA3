#Define dependencies of test files 
test_BitInputStream_exe = executable ('test_BitInputStream.cpp.executable',
    sources: ['test_BitInputStream.cpp'],
    dependencies : [encoder_dep, input_dep, gtest_dep])
test('my BitInputStream test', test_BitInputStream_exe)

test_BitOutputStream_exe = executable ('test_BitOutputStream.cpp.executable',
    sources: ['test_BitOutputStream.cpp'],
    dependencies : [encoder_dep, output_dep, gtest_dep])
test('my BitOutputStream test', test_BitOutputStream_exe)

test_HCTree_exe = executable ('test_HCTree.cpp.executable',
    sources: ['test_HCTree.cpp'],
    dependencies : [encoder_dep, gtest_dep])
test('my HCTree test', test_HCTree_exe)