
# TEJ Suite - Test, Experiment and enJoy Suite
TEJ Suite is a simple testing suite that puts together main development tools: git, cmake and googletest in order to provide a lightweight boilerplate to quickly test and experiment with CPP code.

## How To Start

### Initial setup
- `git clone https://github.com/voyciecho/tejsuite.git --recursive`

### Build
- `mkdir build && cd build && cmake .. && make`

### Run all tests:
- `cd build/src && ./tejsuite`

### Filter tests runs:
- `./tejsuite --gtest_filter=SimpleTest*`
- `./tejsuite --gtest_filter=SimpleTest.ExpectationTest`

### Clean
- `rm -rf build`

## How To Add more joy (tests)
- Create a test file i.e. `test_next.cpp` under `src` folder, similar to `test_simple.cpp`.
- Add the new file under `add_executable(` in the `src/CMakeLists.txt`.
- Rebuild and run.

## TEJ Suite's Name
TEJ Suite sends it's love to the land-of-tejs: Poznan.
