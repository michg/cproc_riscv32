simple tescases running on [picorv32] (https://github.com/cliffordwolf/picorv32)
using the simulator [iverilog] (https://github.com/steveicarus/iverilog)

First build the simulation:
> ./buildsim.sh

Then either run a single test:
> ./run.sh sort

The generated files will be in ./result/sort
The simulation output will be in ./result/sort/sort.log.
Or run all tests:
> ./runall.sh

A summary of the results will be in ./result/results.log.
