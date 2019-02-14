pushd p:\bin
set output_name=%~1
set input_files=%~2
set include_dirs=%~3
set compiler_flags=%~4
set linker_flags=%~5
cl %include_dirs% %compiler_flags% /Fe%output_name%.dll /Fm%output_name%.map %input_files% /link /DLL %linker_flags%
popd