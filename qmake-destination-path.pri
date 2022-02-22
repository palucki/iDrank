platform_path = unknown-platform
#compiler_path = unknown-compiler
#processor_path = unknown-processor
build_path = unknown-build

apptype_path = unknown-type

PLATFORM_WIN {
    platform_path = windows
}
PLATFORM_OSX {
    platform_path = osx
}
PLATFORM_LINUX {
    platform_path = linux
}

android:  apptype_path = mobile
else: apptype_path = desktop

#COMPILER_GCC {
#    compiler_path = gcc
#}
#COMPILER_MSVC2017 {
#    compiler_path = msvc2017
#}
#COMPILER_CLANG {
#    compiler_path = clang
#}

#PROCESSOR_x64 {
#    processor_path = x64
#}
#PROCESSOR_x86 {
#    processor_path = x86
#}

BUILD_DEBUG {
    build_path = debug
} else {
    build_path = release
}
DESTINATION_PATH = $$platform_path/$$apptype_path/$${QT_ARCH}/$$build_path
message(Dest path: $${DESTINATION_PATH})
